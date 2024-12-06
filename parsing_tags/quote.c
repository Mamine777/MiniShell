/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isall <isall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:06:44 by isall             #+#    #+#             */
/*   Updated: 2024/12/02 16:06:44 by isall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_quote_state(char c, int *in_single_quotes,
		int *in_double_quotes)
{
	if (c == '\'' && !(*in_double_quotes))
	{
		*in_single_quotes = !(*in_single_quotes);
	}
	else if (c == '"' && !(*in_single_quotes))
	{
		*in_double_quotes = !(*in_double_quotes);
	}
}

int	should_add_char(char c, int in_single_quotes, int in_double_quotes)
{
	if (c == '\'' && !in_double_quotes)
		return (in_double_quotes);
	else if (c == '"' && !in_single_quotes)
		return (in_single_quotes);
	return (1);
}

char	*ft_quote_remover(char *str, int i, int j)
{
	char	*result;
	char	*temp;
	int		in_single_quotes;
	int		in_double_quotes;

	in_single_quotes = 0;
	in_double_quotes = 0;
	temp = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!temp)
		return (NULL);
	while (str[i])
	{
		update_quote_state(str[i], &in_single_quotes, &in_double_quotes);
		if (should_add_char(str[i], in_single_quotes, in_double_quotes))
			temp[j++] = str[i];
		i++;
	}
	temp[j] = '\0';
	result = ft_strdup(temp);
	free(temp);
	return (result);
}
