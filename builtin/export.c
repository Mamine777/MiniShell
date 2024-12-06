/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isall <isall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:25:24 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/03 17:01:43 by isall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_is_exist2(const char *s, int c)
{
	int				i;
	unsigned char	d;

	if (!s)
		return (0);
	d = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == d && s[i + 1])
			return (1);
		i++;
	}
	return (0);
}

static int	validate(const char *str)
{
	int	i;

	if (!str || !ft_isalpha(str[0]))
		return (1);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	handle_export_tokens(t_stack *stack, char **tokens)
{
	int	i;

	i = 1;
	while (tokens[i])
	{
		if (!validate(tokens[i]))
		{
			if (!extract(tokens[i], stack))
				init_stack(stack, tokens[i]);
		}
		else
			return (ft_printf("Error: not valid identifier\n"), 1);
		i++;
	}
	return (0);
}

int	exc_export(char **tokens, t_data *data, t_stack *stack)
{
	t_lst	*lst;

	if (!tokens || !data || !stack)
		return (1);
	lst = malloc(sizeof(t_lst));
	if (!lst)
		return (perror("malloc"), 1);
	lst->top = NULL;
	fill_second(lst, stack);
	if (!tokens[1])
	{
		printf_second(lst);
		free_list(lst);
		return (0);
	}
	if (handle_export_tokens(stack, tokens))
	{
		free_list(lst);
		return (1);
	}
	free_list(lst);
	return (0);
}
