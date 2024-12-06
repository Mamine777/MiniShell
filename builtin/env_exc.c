/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:43:05 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/02 20:00:36 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if(char *env, char *key)
{
	size_t	key_len;

	key_len = ft_strlen(key);
	if (ft_strncmp(env, key, key_len) == 0)
		return (1);
	return (0);
}

char	*get_pwd_current(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return (NULL);
	}
	return (cwd);
}

static void	*allocate_special_env(t_data *data, int i, char **env)
{
	char	*temp;

	if (check_if(env[i], "PWD="))
		temp = ft_strjoin("PWD=", get_pwd_current());
	else if (check_if(env[i], "OLDPWD="))
		temp = ft_strjoin("OLDPWD=", data->old_pwd);
	else
	{
		data->new_env[i] = ft_strdup(env[i]);
		return (data->new_env[i]);
	}
	if (!temp)
		return (perror("malloc"), NULL);
	data->new_env[i] = ft_strdup(temp);
	free(temp);
	if (!data->new_env[i])
		return (ft_free(data->new_env), perror("env"), NULL);
	return (data->new_env[i]);
}

void	*allocate_env(char **env, t_data *data)
{
	int	i;
	int	j;

	if (!env)
		return (NULL);
	j = 0;
	while (env[j])
		j++;
	data->new_env = malloc(sizeof(char *) * (j + 1));
	if (!data->new_env)
		return (perror("malloc"), NULL);
	i = 0;
	while (i < j - 1)
	{
		if (!allocate_special_env(data, i, env))
			return (NULL);
		i++;
	}
	data->new_env[i] = ft_strdup("_=/usr/bin/env");
	if (!data->new_env[i])
		return (ft_free(data->new_env), perror("env"), NULL);
	data->new_env[i + 1] = NULL;
	return (NULL);
}

int	exc_env(char **token, char **env, t_data *data, t_stack *stack)
{
	(void)data;
	if (!token || !env)
		return (1);
	if (token[1])
	{
		g_exit_status = 127;
		return (perror("env: Too many arguments\n"), 1);
	}
	update_pwd(stack, data);
	printf_stack(stack);
	return (0);
}
