/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:39:36 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/02 19:01:10 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_wavey(char **token, char *home, t_data *data, char *path)
{
	ft_strcpy(path, home);
	ft_strcat(path, token[1] + 1);
	free(data->old_pwd);
	data->old_pwd = ft_strdup("");
	data->old_pwd = ft_strjoin(data->old_pwd, data->pwd);
	if (chdir(path) != 0)
	{
		g_exit_status = 1;
		return (perror("cd"), 1);
	}
	return (0);
}

int	handle_dash(char *home, t_data *data)
{
	(void) home;
	if (!data->old_pwd || *(data->old_pwd) == '\0')
	{
		g_exit_status = 1;
		return (printf("cd : OLDPWD not set\n"), 1);
	}
	data->temp_pwd = data->pwd;
	data->pwd = data->old_pwd;
	data->old_pwd = data->temp_pwd;
	if (chdir(data->pwd) != 0)
	{
		g_exit_status = 1;
		return (printf("cd"), 1);
	}
	printf("%s\n", data->pwd);
	free(data->pwd);
	data->pwd = ft_strdup("");
	data->pwd = ft_strjoin(data->pwd, get_pwd_current());
	return (0);
}

int	double_dash(char *home, t_data *data)
{
	if (!home)
	{
		g_exit_status = 1;
		return (perror("not set\n"), 1);
	}
	free(data->old_pwd);
	data->old_pwd = ft_strdup("");
	data->old_pwd = ft_strjoin(data->old_pwd, data->pwd);
	if (chdir(home) != 0)
	{
		g_exit_status = 1;
		return (perror("cd"), 1);
	}
	return (0);
}

int	open_condition(char **token, t_data *data)
{
	free(data->old_pwd);
	data->old_pwd = ft_strdup("");
	data->old_pwd = ft_strjoin(data->old_pwd, data->pwd);
	if (chdir(token[1]) != 0)
	{
		g_exit_status = 1;
		return (perror("cd:"), 1);
	}
	return (0);
}

int	no_arg(char *home, t_data *data)
{
	if (!home)
	{
		g_exit_status = 1;
		return (perror("not set\n"), 1);
	}
	free(data->old_pwd);
	data->old_pwd = ft_strdup("");
	data->old_pwd = ft_strjoin(data->old_pwd, data->pwd);
	if (chdir(home) != 0)
	{
		g_exit_status = 1;
		return (perror("cd"), 1);
	}
	return (0);
}
