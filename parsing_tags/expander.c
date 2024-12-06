/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isall <isall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:01:24 by isall             #+#    #+#             */
/*   Updated: 2024/12/02 16:01:24 by isall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*handle_normal_char(char *result, char c, int *i)
{
	char	str[2];
	char	*temp;

	str[0] = c;
	str[1] = '\0';
	temp = ft_strjoin(result, str);
	free(result);
	*i += 1;
	return (temp);
}

static char	*handle_single_quotes(char *result, char *str, int *i, t_quote *q)
{
	q->in_single = !q->in_single;
	result = handle_normal_char(result, str[*i], i);
	if (q->in_single)
	{
		while (str[*i] && str[*i] != '\'')
			result = handle_normal_char(result, str[*i], i);
		if (str[*i] == '\'')
		{
			result = handle_normal_char(result, str[*i], i);
			q->in_single = 0;
		}
	}
	return (result);
}

static char	*handle_double_quotes(char *result, char *str, int *i, t_quote *q)
{
	q->in_double = !q->in_double;
	result = handle_normal_char(result, str[*i], i);
	return (result);
}

static char	*handle_dollar_sign(char *result, char *str, int *i, t_quote *q)
{
	if (!q->in_single)
	{
		if (!str[*i + 1] || str[*i + 1] == ' ' || str[*i + 1] == '\"')
			result = handle_normal_char(result, str[*i], i);
		else if (str[*i + 1] == '?' || str[*i + 1] == '$')
			result = handle_special_vars(result, str[*i + 1], i);
		else
			result = handle_env_var(result, str, i);
	}
	else
		result = handle_normal_char(result, str[*i], i);
	return (result);
}

char	*ft_expander(char *str)
{
	t_quote	q;
	int		i;
	char	*result;

	if (!str)
		return (NULL);
	q.in_single = 0;
	q.in_double = 0;
	i = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\'' && !q.in_double)
			result = handle_single_quotes(result, str, &i, &q);
		else if (str[i] == '\"' && !q.in_single)
			result = handle_double_quotes(result, str, &i, &q);
		else if (str[i] == '$')
			result = handle_dollar_sign(result, str, &i, &q);
		else
			result = handle_normal_char(result, str[i], &i);
	}
	return (result);
}
