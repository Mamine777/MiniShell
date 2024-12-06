/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:33:23 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/02 19:01:43 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_home(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

static int	omg_condition(char **token, char *home, t_data *data, char *path)
{
	if (token[1][0] == '~' && token[1])
	{
		if (handle_wavey(token, home, data, path))
			return (1);
	}
	else if (token[1][0] == '-' && token[1][1] == '\0')
	{
		if (handle_dash(home, data))
			return (1);
	}
	else if (token[1][1] == '-' && token[1][1] == '-' && token[1][2] == '\0')
	{
		if (double_dash(home, data))
			return (1);
	}
	else if (token[1])
	{
		if (open_condition(token, data))
			return (1);
	}
	return (0);
}

int	exc_cd(char **token, char **env, t_data *data)
{
	char	*home;
	char	path[1024];

	if (!token || !token[0])
		return (1);
	home = get_home(env);
	if (token[1] && token[1][0] != '\0')
	{
		if (omg_condition(token, home, data, path))
			return (1);
	}
	else
	{
		if (no_arg(home, data))
			return (1);
	}
	free(data->pwd);
	data->pwd = ft_strdup("");
	data->pwd = ft_strjoin(data->pwd, get_pwd_current());
	return (0);
}

int	exc_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	return (0);
}
