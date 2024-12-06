/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:51:11 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/02 18:24:06 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_cmd(char *string, char **env, t_data *data, t_stack *stack)
{
	char	**splited;

	splited = ft_split(string, ' ');
	if (!splited || !splited[0])
		return (1);
	if (splited && splited[0] && ft_strncmp(splited[0], "cd", 3) == 0)
		exc_cd(splited, env, data);
	else if (ft_strncmp(splited[0], "pwd", 4) == 0)
		exc_pwd();
	else if (ft_strncmp(splited[0], "exit", 5) == 0)
		exc_exit(splited, data);
	else if (ft_strncmp(splited[0], "env", 4) == 0)
		exc_env(splited, env, data, stack);
	else if (ft_strncmp(splited[0], "export", 7) == 0)
		exc_export(splited, data, stack);
	else if (ft_strncmp(splited[0], "unset", 6) == 0)
		exc_unset(splited, stack);
	else if (ft_strncmp(splited[0], "echo", 5) == 0)
		echo_built(splited);
	ft_free(splited);
	return (1);
}

int	builtin(char *cmd_line, char **env, t_data *data, t_stack *stack)
{
	(void) data;
	(void) stack;
	if (!cmd_line)
		return (1);
	check_cmd(cmd_line, env, data, stack);
	return (0);
}
