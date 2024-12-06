/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:51:13 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/02 19:51:14 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	is_n_bool(char *token)
{
	int		i;
	bool	n_flag;

	n_flag = false;
	i = 0;
	if (token[i] != '-')
		return (n_flag);
	i++;
	while (token[i] && token[i] == 'n')
		i++;
	if (token[i] == '\0')
		n_flag = true;
	return (n_flag);
}

static void	echo_print_args(char **token, bool n_flag, int i)
{
	if (!token[i])
	{
		if (!n_flag)
			printf("\n");
		return ;
	}
	while (token[i])
	{
		printf("%s", token[i]);
		if (token[i + 1])
			printf(" ");
		else if (!token[i + 1] && !n_flag)
			printf("\n");
		i++;
	}
}

void	echo_built(char **token)
{
	int		i;
	bool	n_bool;

	n_bool = false;
	i = 1;
	while (token[i] && is_n_bool(token[i]))
	{
		n_bool = true;
		i++;
	}
	echo_print_args(token, n_bool, i);
}
