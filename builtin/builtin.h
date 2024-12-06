/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isall <isall@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:52:50 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/03 17:01:51 by isall            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../libft/libft.h"
# include <ctype.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct t_data
{
	char			**new_env;
	char			*pwd;
	char			*old_pwd;
	char			*temp_pwd;
}					t_data;
// list
typedef struct t_nodes
{
	char			*str;
	struct t_nodes	*next;
}					t_nodes;

typedef struct t_stack
{
	t_nodes			*top;
}					t_stack;
// export list
typedef struct t_lol
{
	char			*str;
	struct t_lol	*next;
}					t_lol;

typedef struct t_lst
{
	t_lol			*top;
}					t_lst;
// utils
void				ft_free(char **strs);
void				free_data(t_data *data);
char				*get_home(char **env);
void				init(t_data *data);
// execution
int					exc_pwd(void);
char				*get_pwd_current(void);
int					exc_exit(char **tokens, t_data *data);
int					check_cmd(char *string, char **env, t_data *data,
						t_stack *stack);
int					exc_cd(char **token, char **env, t_data *data);
int					builtin(char *cmd_line, char **env, t_data *data,
						t_stack *stack);
int					exc_env(char **token, char **env, t_data *data,
						t_stack *stack);
void				*allocate_env(char **env, t_data *data);
int					exc_export(char **tokens, t_data *data, t_stack *stack);
int					exc_unset(char **token, t_stack *stack);
// cd utils
int					handle_wavey(char **token, char *home, t_data *data,
						char *path);
int					handle_dash(char *home, t_data *data);
int					double_dash(char *home, t_data *data);
int					open_condition(char **token, t_data *data);
int					no_arg(char *home, t_data *data);
int					extract_env(char *str, t_stack *stack);
// random utils
int					print_env(char **env);
void				printf_second(t_lst *stack);
int					extract(char *str, t_stack *stack);
int					check_is_valid(const char *s, int c);
int					is_builtin(char *input);
int					is_no_pipe(char *input);
void				update_pwd(t_stack *stack, t_data *data);
int					check_if(char *env, char *key);
int					check_is_exist2(const char *s, int c);
void				echo_built(char **token);
void				printf_second(t_lst *stack);
int					extract(char *str, t_stack *stack);
void				printf_stack(t_stack *stack);
int					print_env(char **env);
// list
void				init_stack(t_stack *stack, void *content);
void				fill_stack(t_stack *stack, t_data *data);
void				printf_stack(t_stack *stack);
void				init_second(t_lst *stack, void *content);
void				fill_second(t_lst *list, t_stack *stack);
void				free_stack(t_stack *stack);
void				free_list(t_lst *list);
int					extract(char *str, t_stack *stack);
#endif
