/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isall <isall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:05:56 by isall             #+#    #+#             */
/*   Updated: 2024/12/02 16:06:25 by isall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_quote_2	*init_quote(void)
{
	t_quote_2	*quote;

	quote = malloc(sizeof(t_quote_2));
	if (!quote)
		return (NULL);
	quote->count_single = 0;
	quote->count_double = 0;
	return (quote);
}

int	needs_continuation(char *str, t_quote_2 *quote)
{
	int	i;

	i = ft_strlen(str) - 1;
	return (str[i] == '|' || quote->count_double % 2 != 0 || quote->count_single
		% 2 != 0);
}

char	*process_line(char *line, t_quote_2 *quote)
{
	char	*trimmed;

	if (!line)
		return (NULL);
	trimmed = ft_strtrim(line, " ");
	free(line);
	if (!trimmed)
		return (NULL);
	check_quote(trimmed, quote);
	return (trimmed);
}

int	is_complete(char *trimmed, t_quote_2 *quote)
{
	int	i;

	i = ft_strlen(trimmed) - 1;
	return (i >= 0 && trimmed[i] != '|' && quote->count_single % 2 == 0
		&& quote->count_double % 2 == 0);
}

char	*handle_continuation(char *str, t_quote_2 *quote)
{
	char	*line;
	char	*trimmed;
	char	*result;

	while (1)
	{
		line = readline("> ");
		trimmed = process_line(line, quote);
		if (!trimmed)
		{
			free(quote);
			return (NULL);
		}
		if (is_complete(trimmed, quote))
		{
			result = ft_strjoin(str, trimmed);
			free(trimmed);
			free(quote);
			return (result);
		}
		free(trimmed);
	}
}
