/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isall <isall@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:54:23 by mokariou          #+#    #+#             */
/*   Updated: 2024/11/30 11:35:39 by isall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_no_pipe(char *input)
{
	int	i;

	i = -1;
	while (++i, input[i])
		if (input[i] == '|')
			return (1);
	return (0);
}

int	is_builtin(char *input)
{
	char	**splited;

	splited = ft_split(input, ' ');
	if (!splited)
		return (0);
	if (ft_strncmp(splited[0], "cd", 3) || ft_strncmp(splited[0], "cd", 3)
		|| ft_strncmp(splited[0], "pwd", 4) || ft_strncmp(splited[0], "exit", 5)
		|| ft_strncmp(splited[0], "env", 4) || ft_strncmp(splited[0], "export",
			7) || ft_strncmp(splited[0], "unset", 6))
		return (1);
	return (0);
}
