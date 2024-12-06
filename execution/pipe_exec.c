/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isall <isall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:18:49 by isall             #+#    #+#             */
/*   Updated: 2024/12/02 17:51:41 by isall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_pipe_data(t_pipe_data *pd, t_type *first,
	t_pipex *info, t_data *data)
{
	pd->first = first;
	pd->current = first;
	pd->last = ft_lstlast2(first);
	pd->info = info;
	pd->data = data;
	pd->prev_fd = -1;
}

void	ft_first(t_type *current, t_type *first, int prev_fd)
{
	if (current != first && prev_fd != -1)
	{
		if (current->indirection == 0)
		{
			dup2(prev_fd, 0);
			close(prev_fd);
		}
	}
}

void	ft_last(t_type *current, t_type *last, int pipe_out, int pipe_in)
{
	if (current != last)
	{
		if (current->outdirection == 0)
		{
			dup2(pipe_out, 1);
			close(pipe_out);
			close(pipe_in);
		}
	}
}

void	ft_pipe_launch(t_type *current, t_type *last, int pipe_fd[2])
{
	if (current != last)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
}
