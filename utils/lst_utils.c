/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isall <isall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:14:02 by isall             #+#    #+#             */
/*   Updated: 2024/12/02 16:14:04 by isall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back2(t_type **lst, t_type *new)
{
	t_type	*current;

	current = *lst;
	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new;
}

int	ft_lstsize2(t_type *lst)
{
	t_type	*current;
	int		i;

	current = lst;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

t_type	*ft_lstlast2(t_type *lst)
{
	t_type	*current;

	if (lst == NULL)
		return (NULL);
	current = lst;
	while (current->next != NULL)
	{
		current = current->next;
	}
	return (current);
}
