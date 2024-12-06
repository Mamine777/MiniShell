/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tag_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isall <isall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:10:12 by isall             #+#    #+#             */
/*   Updated: 2024/12/02 16:10:15 by isall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_filename(char *str, int *i)
{
	int		j;
	char	*filename;

	while (str[*i] == ' ')
		(*i)++;
	j = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '<' && str[*i] != '>')
		(*i)++;
	filename = ft_strndup(str + j, *i - j);
	return (filename);
}

static int	count_input_redirections(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '<' && !is_in_quotes(str, i))
		{
			if (str[i + 1] == '<')
				i += 2;
			else
				count++;
		}
		i++;
	}
	return (count);
}

static int	count_output_redirections(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '>' && !is_in_quotes(str, i))
		{
			if (str[i + 1] == '>')
				i += 2;
			else
				count++;
		}
		i++;
	}
	return (count);
}

char	**ft_parse_input_redirections(char *str)
{
	int		i;
	int		k;
	char	**tab;

	tab = malloc((count_input_redirections(str) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '<' && !is_in_quotes(str, i))
		{
			if (str[i + 1] == '<')
				i += 2;
			else
			{
				i++;
				tab[k++] = extract_filename(str, &i);
			}
		}
		i++;
	}
	tab[k] = NULL;
	return (tab);
}

char	**ft_parse_output_redirections(char *str)
{
	int		i;
	int		k;
	char	**tab;

	tab = malloc((count_output_redirections(str) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '>' && !is_in_quotes(str, i))
		{
			if (str[i + 1] == '>')
				i += 2;
			else
			{
				i++;
				tab[k++] = extract_filename(str, &i);
			}
		}
		i++;
	}
	tab[k] = NULL;
	return (tab);
}
