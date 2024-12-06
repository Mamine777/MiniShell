/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_exc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:22:20 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/02 19:19:22 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	commit_exit(char **tokens, t_data *data)
{
	int	i;

	i = -1;
	while (tokens[1][++i])
	{
		if (!ft_isdigit(tokens[1][i]) && tokens[1][i] != '-'
			&& tokens[1][i] != '+')
		{
			g_exit_status = 255;
			return (ft_free(tokens), perror("numeric argument required\n"),
				free_data(data), exit(g_exit_status), 1);
		}
		else if (tokens[2] != NULL)
		{
			g_exit_status = 1;
			return (perror("exit :too many argumetns\n"), 1);
		}
		g_exit_status = ft_atoi(tokens[1]) % 256;
		ft_free(tokens);
		free_data(data);
		exit(g_exit_status);
	}
	return (0);
}

int	exc_exit(char **tokens, t_data *data)
{
	if (tokens[1])
	{
		if (commit_exit(tokens, data))
			return (1);
	}
	else
	{
		free_data(data);
		ft_free(tokens);
		exit(g_exit_status);
	}
	return (0);
}
