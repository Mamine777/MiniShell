/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:13:21 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/02 18:17:08 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	init_second(t_lst *stack, void *content)
{
	t_lol	*new_node;
	t_lol	*current;

	if (!stack || !content)
		return ;
	new_node = malloc(sizeof(t_lol));
	if (!new_node)
		return ;
	new_node->str = ft_strjoin("declare -x ", (char *)content);
	if (!new_node->str)
		return (free(new_node));
	new_node->next = NULL;
	if (!stack->top)
	{
		stack->top = new_node;
		return ;
	}
	current = stack->top;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void	free_list(t_lst *list)
{
	t_lol	*temp;

	if (!list)
		return ;
	while (list->top != NULL)
	{
		temp = list->top->next;
		free(list->top->str);
		free(list->top);
		list->top = temp;
	}
	list->top = NULL;
}

void	free_stack(t_stack *stack)
{
	t_nodes	*current;
	t_nodes	*temp;

	if (!stack)
		return ;
	current = stack->top;
	while (current)
	{
		temp = current->next;
		free(current->str);
		free(current);
		current = temp;
	}
	stack->top = NULL;
}

void	fill_second(t_lst *list, t_stack *stack)
{
	int		i;
	int		len;
	t_nodes	*current;

	if (!stack || !list)
		return ;
	len = 0;
	current = stack->top;
	while (current)
	{
		len++;
		current = current->next;
	}
	current = stack->top;
	i = 0;
	while (i < len)
	{
		init_second(list, current->str);
		current = current->next;
		i++;
	}
}
