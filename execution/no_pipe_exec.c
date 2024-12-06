/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isall <isall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:19:04 by isall             #+#    #+#             */
/*   Updated: 2024/12/02 16:19:10 by isall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_change_outfile(t_type *head)
{
	int	outfile;

	outfile = 0;
	ft_outfile(head);
	ft_outfile_2(head);
	if (head->last_out == 1)
		outfile = open(head->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else if (head->last_out == 2)
		outfile = open(head->outfile, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (outfile == -1)
	{
		g_exit_status = EXIT_FAILURE;
		perror(head->outfile);
		exit(g_exit_status);
	}
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		close(outfile);
		g_exit_status = EXIT_FAILURE;
		perror("dup2 output");
		exit(g_exit_status);
	}
	close(outfile);
}

void	ft_change_infile(t_type *head)
{
	if (head->infile_fd == -1)
	{
		g_exit_status = EXIT_FAILURE;
		perror("input file");
		exit(g_exit_status);
	}
	if (dup2(head->infile_fd, STDIN_FILENO) == -1)
	{
		close(head->infile_fd);
		g_exit_status = EXIT_FAILURE;
		perror("dup2 input");
		exit(g_exit_status);
	}
	close(head->infile_fd);
	head->infile_fd = -1;
}
