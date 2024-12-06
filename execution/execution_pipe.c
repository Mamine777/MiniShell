/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isall <isall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:50:08 by isall             #+#    #+#             */
/*   Updated: 2024/12/03 15:04:53 by isall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_child_redirections(t_type *current)
{
	if (current->indirection > 0)
		ft_change_infile(current);
	if (current->outdirection > 0)
		ft_change_outfile(current);
}

static void	handle_parent(t_pipe_data *pd)
{
	if (pd->current != pd->last)
		close(pd->pipe_fd[1]);
	pd->prev_fd = pd->pipe_fd[0];
}

static void	handle_child_process(t_pipe_data *pd)
{
	handle_child_redirections(pd->current);
	ft_first(pd->current, pd->first, pd->prev_fd);
	ft_last(pd->current, pd->last, pd->pipe_fd[1], pd->pipe_fd[0]);
	if (pd->current->cmd[0] != '\0')
	{
		if (is_builtin_cmd(pd->current->cmd))
		{
			check_cmd(pd->current->cmd, pd->info->env, pd->data, pd->stack);
			exit(g_exit_status);
		}
		else
			ft_execute(pd->info->env, pd->current->cmd, pd->stack);
	}
	exit(g_exit_status);
}

static void	wait_for_children(int *last_status)
{
	int	status;

	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			*last_status = WEXITSTATUS(status);
	}
}

void	ft_pipe(t_type *first, t_pipex *info, t_data *data, t_stack *stack)
{
	t_pipe_data	pd;
	pid_t		pid;
	int			last_status;

	last_status = 0;
	init_pipe_data(&pd, first, info, data);
	pd.stack = stack;
	while (pd.current)
	{
		ft_pipe_launch(pd.current, pd.last, pd.pipe_fd);
		pid = fork();
		signal(SIGINT, ft_exec_sig_handler);
		signal(SIGQUIT, ft_exec_sig_handler);
		if (pid == 0)
			handle_child_process(&pd);
		handle_parent(&pd);
		pd.current = pd.current->next;
	}
	wait_for_children(&last_status);
	g_exit_status = last_status;
}
