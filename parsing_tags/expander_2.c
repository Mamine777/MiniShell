/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isall <isall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:59:20 by isall             #+#    #+#             */
/*   Updated: 2024/12/02 15:59:40 by isall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_var(char *var_name)
{
	char	*value;
	char	*cleaned_var_name;

	cleaned_var_name = var_name;
	if (cleaned_var_name[0] == '$')
		cleaned_var_name++;
	value = getenv(cleaned_var_name);
	if (value == NULL)
		return (NULL);
	return (ft_strdup(value));
}

char	*handle_special_vars(char *result, char c, int *i)
{
	char	*expanded_var;
	char	*temp;

	if (c == '?')
	{
		expanded_var = ft_itoa(g_exit_status);
		*i += 2;
	}
	else
	{
		expanded_var = ft_itoa(getpid());
		*i += 2;
	}
	temp = ft_strjoin(result, expanded_var);
	free(result);
	free(expanded_var);
	return (temp);
}

static char	*handle_empty_var(char *result, int *i)
{
	char	*temp;

	temp = ft_strjoin(result, "$");
	free(result);
	*i += 1;
	return (temp);
}

char	*handle_env_var(char *result, char *str, int *i)
{
	int		j;
	char	*var_name;
	char	*expanded_var;
	char	*temp;

	j = *i + 1;
	while (str[j] && str[j] != ' ' && str[j] != '$' && str[j] != '\''
		&& str[j] != '\"')
		j++;
	if (j == *i + 1)
		return (handle_empty_var(result, i));
	var_name = ft_strndup(str + *i + 1, j - *i - 1);
	expanded_var = get_env_var(var_name);
	free(var_name);
	if (expanded_var)
	{
		temp = ft_strjoin(result, expanded_var);
		free(result);
		free(expanded_var);
		result = temp;
	}
	*i = j;
	return (result);
}
