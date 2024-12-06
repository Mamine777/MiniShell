# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isall <isall@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/01 14:51:32 by mokariou          #+#    #+#              #
#    Updated: 2024/12/02 20:47:28 by isall            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I/Users/$(shell whoami)/homebrew/opt/readline/include
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I$(LIBFT_DIR) -I.
PRE_EXEC = ./execution/
PRE_PARSING = ./parsing_tags/
PRE_UTILS = ./utils/
PRE_SRCS = ./
PRE_BUILTIN = ./builtin/
OBJ_DIR = ./obj

SRC_EXEC = execution.c no_pipe_exec.c path_execve_cmd.c pipe_exec.c execution_pipe.c
SRC_PARSING = parsing.c tag.c tag_utils.c expander.c quote.c expander_2.c tag_2.c tag_command.c parsing_2.c freezer.c init_parsing.c token_check.c
SRC_UTILS = lst_utils.c open_file.c ft_split2.c utils.c
SRC_MAIN = main.c main_2.c
SRC_BUILTIN = builtin.c cd_utils.c env_exc.c exc_cd.c \
			exit_exc.c export.c utils_data.c exc_unset.c \
			check1.c echo.c utils.c extra_sho.c utils_export.c

SRCS = $(addprefix $(PRE_EXEC), $(SRC_EXEC)) \
       $(addprefix $(PRE_PARSING), $(SRC_PARSING)) \
       $(addprefix $(PRE_UTILS), $(SRC_UTILS)) \
       $(addprefix $(PRE_SRCS), $(SRC_MAIN)) \
       $(addprefix $(PRE_BUILTIN), $(SRC_BUILTIN))

OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBFT) -lreadline -L/Users/$(shell whoami)/homebrew/opt/readline/lib

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
