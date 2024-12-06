/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isall <isall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:26:05 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/03 14:56:59 by isall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtin/builtin.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_NOT_EXECUTABLE 126
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_INVALID_ARGUMENT 128

extern int			g_exit_status;

typedef struct s_type
{
	char			*cmd;
	char			**redirection_in;
	char			**redirection_out;
	char			**outfile_append;
	char			**here_doc;
	char			*infile;
	char			*outfile;
	int				infile_fd;
	int				last_in;
	int				last_out;
	int				indirection;
	int				outdirection;
	struct s_type	*next;
}					t_type;
typedef struct s_pipex
{
	int				ac;
	char			**av;
	char			**env;
}					t_pipex;

typedef struct s_size_calc
{
	int				size;
	int				var_size;
	char			**env;
}					t_size_calc;

typedef struct s_quote_2
{
	int				count_single;
	int				count_double;
}					t_quote_2;

typedef struct s_quote
{
	int				in_single;
	int				in_double;
}					t_quote;

typedef struct s_split
{
	int				count;
	int				i;
	int				start;
	char			in_simple_quote;
	char			in_double_quote;
}					t_split;

typedef struct s_pipe_data
{
	t_type			*first;
	t_type			*current;
	t_type			*last;
	t_pipex			*info;
	t_data			*data;
	t_stack			*stack;
	int				pipe_fd[2];
	int				prev_fd;
}					t_pipe_data;
// parsing
t_type				*init_list(char *input, t_pipex *info);
char				*get_env_var(char *var_name);
char				*ft_expander(char *str);
char				*ft_quote_remover(char *str, int i, int j);
int					ft_check_forbidden(char *str);
char				*handle_special_vars(char *result, char c, int *i);
char				*handle_env_var(char *result, char *str, int *i);
int					token_checker(char *rl);

// tag
int					determine_redirection_type(char *str, int type, int i);
int					determine_redirection_type_2(char *str);
int					determine_last_in_type(char *str);
int					determine_last_out_type(char *str);
char				**ft_parse_input_redirections(char *str);
char				**ft_parse_output_redirections(char *str);
char				**ft_parse_here_doc(char *str);
char				**ft_parse_outfile_append(char *str);
char				*ft_command(char *str);
int					is_in_quotes(const char *str, int pos);
char				*extract_filename(char *str, int *i);
t_quote_2			*init_quote(void);
int					needs_continuation(char *str, t_quote_2 *quote);
char				*process_line(char *line, t_quote_2 *quote);
int					is_complete(char *trimmed, t_quote_2 *quote);
char				*handle_continuation(char *str, t_quote_2 *quote);
void				check_quote(char *str, t_quote_2 *quote);
char				*ft_check_last(char *str);
void				ft_in(t_type *head);

// functions utils
void				ft_lstadd_back2(t_type **lst, t_type *new);
int					ft_lstsize2(t_type *lst);
t_type				*ft_lstlast2(t_type *lst);
char				**ft_split_quote(char *str, char sep);
char				*ft_strndup(const char *s, size_t n);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strcpy(char *dest, const char *src);

// execute
void				ft_execute(char **env, char *path, t_stack *stack);
void				ft_infile(t_type *head);
void				ft_outfile(t_type *head);
void				handle_here_doc(char *limiter, t_type *head);
int					is_builtin_cmd(char *cmd);

// main
t_pipex				*init_info(int ac, char **av, char **env);
void				reset_terminal_line(void);
void				signal_handler_main(int signum);
void				ft_exec_sig_handler(int sig);
void				cleanup_resources(t_pipex *info, t_data *data,
						t_stack *stack);

// execute simple
void				ft_no_pipe(t_type *head, t_pipex *info, t_stack *stack,
						t_data *data);
void				ft_change_infile(t_type *head);
void				ft_change_outfile(t_type *head);
void				ft_outfile_2(t_type *head);

// execute multiple
void				ft_pipe(t_type *first, t_pipex *info, t_data *data,
						t_stack *stack);
void				ft_first(t_type *current, t_type *first, int prev_fd);
void				ft_last(t_type *current, t_type *last, int pipe_out,
						int pipe_in);
void				ft_pipe_launch(t_type *current, t_type *last,
						int pipe_fd[2]);
void				init_pipe_data(t_pipe_data *pd, t_type *first,
						t_pipex *info, t_data *data);

// FREEZER
void				free_db(char **tab);
void				ft_free_list(t_type *head);
void				free_str_array(char **array);

#endif