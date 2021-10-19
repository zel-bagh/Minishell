#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include <errno.h>

typedef struct	s_redirections
{
	char					*file;
	int						type;
	struct s_redirections	*next;
}							t_red;

typedef struct	s_cmd
{
	char			**args;
	t_red			*red;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

#endif

//type : > = 1 : >> = 2 : < = 3 : << : 4 