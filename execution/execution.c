/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isall <isall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:52:22 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/03 14:57:20 by isall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin_cmd(char *cmd)
{
	char	**split;
	int		result;

	if (!cmd || cmd[0] == '\0')
		return (0);
	split = ft_split(cmd, ' ');
	if (!split)
		return (0);
	result = (split[0] && (ft_strncmp(split[0], "cd", 3) == 0
				|| ft_strncmp(split[0], "pwd", 4) == 0 || ft_strncmp(split[0],
					"exit", 5) == 0 || ft_strncmp(split[0], "env", 4) == 0
				|| ft_strncmp(split[0], "export", 7) == 0
				|| ft_strncmp(split[0], "unset", 6) == 0 || ft_strncmp(split[0],
					"echo", 5) == 0));
	ft_free(split);
	return (result);
}

void	execute_builtin_redir(t_type *cmd_info, t_pipex *info, t_data *data,
		t_stack *stack)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		if (cmd_info->indirection > 0)
			ft_change_infile(cmd_info);
		if (cmd_info->outdirection > 0)
			ft_change_outfile(cmd_info);
		check_cmd(cmd_info->cmd, info->env, data, stack);
		exit(g_exit_status);
	}
	waitpid(pid, &status, 0);
}

void	execute_external(t_type *cmd_info, t_pipex *info, t_stack *stack)
{
	pid_t	pid;
	int		status;

	pid = fork();
	signal(SIGINT, ft_exec_sig_handler);
	signal(SIGQUIT, ft_exec_sig_handler);
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (cmd_info->indirection > 0)
			ft_change_infile(cmd_info);
		if (cmd_info->outdirection > 0)
			ft_change_outfile(cmd_info);
		ft_execute(info->env, cmd_info->cmd, stack);
		exit(g_exit_status);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
}

void	ft_no_pipe(t_type *head, t_pipex *info, t_stack *stack, t_data *data)
{
	if (!head || !head->cmd || head->cmd[0] == '\0')
		return ;
	if (is_builtin_cmd(head->cmd))
	{
		if (head->indirection > 0 || head->outdirection > 0)
			execute_builtin_redir(head, info, data, stack);
		else
			check_cmd(head->cmd, info->env, data, stack);
	}
	else
		execute_external(head, info, stack);
}
