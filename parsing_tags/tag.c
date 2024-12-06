/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tag.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isall <isall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:11:30 by isall             #+#    #+#             */
/*   Updated: 2024/12/02 16:11:32 by isall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_in_quotes(const char *str, int pos)
{
	int	single_quote;
	int	double_quote;
	int	i;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (i < pos)
	{
		if (str[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (str[i] == '\"' && !single_quote)
			double_quote = !double_quote;
		i++;
	}
	return (single_quote || double_quote);
}

static int	count_here_doc(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<' && !is_in_quotes(str, i))
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}

static int	count_outfile_append(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>' && !is_in_quotes(str, i))
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}

char	**ft_parse_here_doc(char *str)
{
	int		i;
	int		k;
	char	**tab;

	tab = malloc((count_here_doc(str) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<' && !is_in_quotes(str, i))
		{
			i += 2;
			tab[k++] = extract_filename(str, &i);
		}
		else
			i++;
	}
	tab[k] = NULL;
	return (tab);
}

char	**ft_parse_outfile_append(char *str)
{
	int		i;
	int		k;
	char	**tab;

	tab = malloc((count_outfile_append(str) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>' && !is_in_quotes(str, i))
		{
			i += 2;
			tab[k++] = extract_filename(str, &i);
		}
		else
			i++;
	}
	tab[k] = NULL;
	return (tab);
}
