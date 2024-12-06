/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:52:55 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/02 19:52:23 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_is_valid(const char *s, int c)
{
	int				i;
	unsigned char	d;

	if (!s)
		return (0);
	d = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) || s[i] == d)
		{
			g_exit_status = 1;
			return (printf("unset : %s: not Valid Argument", s), 1);
		}
		i++;
	}
	return (0);
}

int	extract_env(char *str, t_stack *stack)
{
	t_nodes	*current;
	size_t	key_len;
	t_nodes	*temp;

	if (!str || !stack || !stack->top)
		return (0);
	key_len = ft_strlen(str);
	current = stack->top;
	if (!ft_strncmp(current->str, str, key_len))
	{
		stack->top = current->next;
		free(current->str);
		return (free(current), 1);
	}
	while (current->next)
	{
		if (!ft_strncmp(current->next->str, str, key_len))
		{
			temp = current->next;
			current->next = temp->next;
			return (free(temp->str), free(temp), 1);
		}
		current = current->next;
	}
	return (0);
}

int	exc_unset(char **token, t_stack *stack)
{
	int	i;

	if (!token || !stack || !stack->top)
		return (1);
	i = 1;
	while (token[i])
	{
		if (check_is_valid(token[i], '='))
		{
			i++;
			continue ;
		}
		else
			extract_env(token[i], stack);
		i++;
	}
	return (0);
}
