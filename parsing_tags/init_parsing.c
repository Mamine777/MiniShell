/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isall <isall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:05:14 by isall             #+#    #+#             */
/*   Updated: 2024/12/02 20:27:36 by isall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_type	*init_node(char *str)
{
	t_type	*node;

	node = malloc(sizeof(t_type));
	if (!node)
		return (NULL);
	node->cmd = ft_command(str);
	node->redirection_in = ft_parse_input_redirections(str);
	node->here_doc = ft_parse_here_doc(str);
	node->last_in = determine_last_in_type(str);
	node->redirection_out = ft_parse_output_redirections(str);
	node->outfile_append = ft_parse_outfile_append(str);
	node->last_out = determine_last_out_type(str);
	node->indirection = determine_redirection_type(str, 0, 0);
	node->outdirection = determine_redirection_type_2(str);
	node->infile_fd = -1;
	node->infile = NULL;
	node->outfile = NULL;
	node->next = NULL;
	free(str);
	return (node);
}

t_type	*init_list(char *input, t_pipex *info)
{
	t_type	*node;
	t_type	*head;
	char	**tab;
	int		i;

	info->ac = 4;
	input = ft_strtrim(input, " ");
	input = ft_check_last(input);
	tab = ft_split_quote(input, '|');
	i = 0;
	head = NULL;
	while (tab[i])
	{
		tab[i] = ft_strtrim(tab[i], " ");
		node = init_node(tab[i]);
		ft_in(node);
		if (head == NULL)
			head = node;
		else
			ft_lstadd_back2(&head, node);
		i++;
	}
	g_exit_status = 0;
	return (head);
}
