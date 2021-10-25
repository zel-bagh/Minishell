# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/02 17:45:42 by zel-bagh          #+#    #+#              #
#    Updated: 2021/10/24 09:29:41 by zel-bagh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mini

SRC = Minishell.c \
	functions.c \
	executing_commands.c \
	childprocess.c \
	heredoc.c

all : $(NAME)

$(NAME) : $(SRC)
	gcc -Wall -Wextra -Werror -lreadline $(SRC) -o $(NAME)

clean :
	rm -rf $(NAME)

fclean: clean

re : fclean all	