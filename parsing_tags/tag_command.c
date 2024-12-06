/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tag_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isall <isall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:10:42 by isall             #+#    #+#             */
/*   Updated: 2024/12/02 16:10:45 by isall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_redirection(char *str, int *i)
{
	if (str[*i + 1] == str[*i])
		*i += 2;
	else
		(*i)++;
	while (str[*i] == ' ' && str[*i])
		(*i)++;
	while (str[*i] && str[*i] != ' ' && str[*i] != '<' && str[*i] != '>')
		(*i)++;
}

static void	skip_redirections(char *str, int *i)
{
	if (str[*i] == '<')
		skip_redirection(str, i);
	else if (str[*i] == '>')
		skip_redirection(str, i);
}

static char	*process_command_part(char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*expanded;
	char	*with_space;

	j = *i;
	while (str[*i] && str[*i] != '<' && str[*i] != '>')
		(*i)++;
	tmp = ft_strndup(str + j, *i - j);
	expanded = ft_expander(tmp);
	free(tmp);
	tmp = ft_quote_remover(expanded, 0, 0);
	free(expanded);
	with_space = ft_strjoin(tmp, " ");
	free(tmp);
	return (with_space);
}

char	*ft_command(char *str)
{
	int		i;
	char	*commande;
	char	*tmp;
	char	*new_cmd;

	if (!str)
		return (NULL);
	i = 0;
	commande = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
			skip_redirections(str, &i);
		else if (str[i] == ' ')
			i++;
		else
		{
			tmp = process_command_part(str, &i);
			new_cmd = ft_strjoin(commande, tmp);
			free(commande);
			free(tmp);
			commande = new_cmd;
		}
	}
	return (commande);
}
