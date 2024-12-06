/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freezer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isall <isall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:03:14 by isall             #+#    #+#             */
/*   Updated: 2024/12/02 18:03:15 by isall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_str_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_free_list(t_type *head)
{
	t_type	*current;
	t_type	*next;

	current = head;
	while (current)
	{
		if (current->cmd && current->cmd[0] != '\0')
			free(current->cmd);
		if (current->redirection_in)
			free_str_array(current->redirection_in);
		if (current->here_doc)
			free_str_array(current->here_doc);
		if (current->redirection_out)
			free_str_array(current->redirection_out);
		if (current->outfile_append)
			free_str_array(current->outfile_append);
		if (current->infile)
			free(current->infile);
		if (current->outfile)
			free(current->outfile);
		next = current->next;
		free(current);
		current = next;
	}
}
