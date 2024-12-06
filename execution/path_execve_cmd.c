/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_execve_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isall <isall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:04:53 by isall             #+#    #+#             */
/*   Updated: 2024/12/02 18:04:55 by isall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_path_3(char **env)
{
	char	*path;
	char	**path_2;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			path = env[i];
			path_2 = ft_split(path + 5, ':');
			if (!path_2)
			{
				perror("split failed");
				exit(1);
			}
		}
		i++;
	}
	return (path_2);
}

char	**get_path_2(t_stack *stack)
{
	int		i;
	t_nodes	*current;

	i = 0;
	current = stack->top;
	while (current)
	{
		if (ft_strncmp(current->str, "PATH", 4) == 0)
		{
			return (ft_split(current->str + 5, ':'));
		}
		current = current->next;
	}
	return (NULL);
}

char	*get_path(char **env, char *cmd, t_stack *stack, int i)
{
	char	**path_2;
	char	*path;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	(void)env;
	path_2 = get_path_2(stack);
	if (!path_2)
		return (NULL);
	while (path_2[i])
	{
		path = ft_strjoin(path_2[i], "/");
		if (!path)
			break ;
		path = ft_strjoin(path, cmd);
		if (access(path, X_OK) == 0)
		{
			free_str_array(path_2);
			return (path);
		}
		i++;
	}
	free_str_array(path_2);
	return (NULL);
}

static char	*prepare_command(char *path, char ***split)
{
	char	*trimmed_path;

	trimmed_path = ft_strtrim(path, " ");
	if (!trimmed_path)
	{
		g_exit_status = EXIT_FAILURE;
		exit(g_exit_status);
	}
	*split = ft_split(trimmed_path, ' ');
	free(trimmed_path);
	if (!*split)
	{
		g_exit_status = EXIT_FAILURE;
		perror("split failed");
		exit(g_exit_status);
	}
	return ((*split)[0]);
}

void	ft_execute(char **env, char *path, t_stack *stack)
{
	char	**split;
	char	*cmd;
	char	*cmd_path;

	cmd = prepare_command(path, &split);
	if (access(cmd, X_OK) != 0)
	{
		cmd_path = get_path(env, cmd, stack, 0);
		if (!cmd_path)
		{
			g_exit_status = EXIT_CMD_NOT_FOUND;
			fprintf(stderr, "Command not found: %s\n", cmd);
			free_str_array(split);
			exit(g_exit_status);
		}
	}
	else
		cmd_path = ft_strdup(cmd);
	execve(cmd_path, split, env);
	g_exit_status = EXIT_NOT_EXECUTABLE;
	perror("execve");
	free(cmd_path);
	free_str_array(split);
	exit(g_exit_status);
}
