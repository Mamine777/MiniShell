/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:37:05 by isall             #+#    #+#             */
/*   Updated: 2024/12/03 18:15:57 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipex	*init_info(int ac, char **av, char **env)
{
	t_pipex	*info;

	info = malloc(sizeof(t_pipex));
	if (!info)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	info->av = av;
	info->env = env;
	info->ac = ac;
	return (info);
}

void	reset_terminal_line(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	signal_handler_main(int signum)
{
	struct termios	term;

	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 1;
	}
	tcgetattr(1, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSANOW, &term);
}

void	ft_exec_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		g_exit_status = 130;
	}
	if (sig == SIGQUIT)
	{
		ft_printf_fd(2, "^\\Quit : 3\n");
		g_exit_status = 131;
	}
}

void	cleanup_resources(t_pipex *info, t_data *data, t_stack *stack)
{
	if (data)
		free_data(data);
	if (stack)
		free_stack(stack);
	if (info)
		free(info);
}
