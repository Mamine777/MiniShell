/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isall <isall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:01:59 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/02 15:36:45 by isall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_in(t_type *head)
{
	int	i;

	if (head->indirection == 2 || head->indirection == 3)
	{
		i = 0;
		while (head->here_doc[i])
		{
			handle_here_doc(head->here_doc[i], head);
			i++;
		}
	}
	if (head->indirection == 1 || head->indirection == 3)
		ft_infile(head);
}

void	check_quote(char *str, t_quote_2 *quote)
{
	int	k;

	k = 0;
	while (str[k])
	{
		if (str[k] == '"')
			quote->count_double++;
		if (str[k] == '\'')
			quote->count_single++;
		k++;
	}
}

char	*ft_check_last(char *str)
{
	t_quote_2	*quote;

	quote = init_quote();
	if (!quote)
		return (NULL);
	check_quote(str, quote);
	if (needs_continuation(str, quote))
		return (handle_continuation(str, quote));
	free(quote);
	return (ft_strdup(str));
}

int	ft_check_forbidden(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ';' || str[i] == '\\')
		{
			ft_printf_fd(2, "Error: forbidden character '%c' detected\n",
				str[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
