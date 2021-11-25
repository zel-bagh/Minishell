# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/02 17:45:42 by zel-bagh          #+#    #+#              #
#    Updated: 2021/11/25 12:03:34 by zel-bagh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mini

SRC = Minishell.c \
	functions.c \
	executing_commands.c \
	childprocess.c \
	heredoc.c \
	shell_builtin.c \
	managing_files_errors.c \
	execute_in_childprocess.c \
	ft_split.c \
	execute_in_childprocess2.c \
	export.c \
	unset.c

all : $(NAME)

$(NAME) : $(SRC)
	gcc -Wall -Wextra -Werror -lreadline $(SRC) -o $(NAME)

clean :
	rm -rf $(NAME)

fclean: clean

re : fclean all	