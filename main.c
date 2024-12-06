/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:48:01 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/03 18:14:38 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_exit_status = 0;

int	initialize_structures(t_data **data, t_stack **stack)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
	{
		perror("malloc");
		return (0);
	}
	init(*data);
	*stack = malloc(sizeof(t_stack));
	if (!*stack)
	{
		free_data(*data);
		perror("malloc");
		return (0);
	}
	(*stack)->top = NULL;
	return (1);
}

void	process_command(char *input, t_pipex *info, t_data *data,
		t_stack *stack)
{
	t_type	*head;

	if (ft_check_forbidden(input))
	{
		free(input);
		return ;
	}
	head = init_list(input, info);
	free(input);
	if (!head)
		return ;
	if (ft_lstsize2(head) > 1)
		ft_pipe(head, info, data, stack);
	else
		ft_no_pipe(head, info, stack, data);
	ft_free_list(head);
}

static void	handle_command(char *input, t_pipex *info, t_data *data,
		t_stack *stack)
{
	if (*input)
	{
		add_history(input);
		allocate_env(info->env, data);
		if (!stack->top)
			fill_stack(stack, data);
		process_command(input, info, data, stack);
	}
	else
		free(input);
}

void	minishell_loop(t_pipex *info, t_data *data, t_stack *stack)
{
	char	*input;

	while (1)
	{
		signal(SIGINT, signal_handler_main);
		signal(SIGQUIT, SIG_IGN);
		input = readline("$minishell $ ");
		if (!input)
		{
			printf("Exit\n");
			break ;
		}
		if (token_checker(input) == 1)
		{
			free(input);
			continue ;
		}
		handle_command(input, info, data, stack);
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipex	*info;
	t_data	*data;
	t_stack	*stack;

	info = init_info(ac, av, env);
	if (!initialize_structures(&data, &stack))
		return (EXIT_FAILURE);
	minishell_loop(info, data, stack);
	cleanup_resources(info, data, stack);
	return (g_exit_status);
}
