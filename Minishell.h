#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <readline/readline.h>

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

typedef struct s_heredoc
{
	int	heredoc_pipe_input_fd;
	int index;
}					t_hdoc;

int		ft_strlen(const char *a);
char*	ft_strjoin(const char *a, const char *b);
int		ft_str_compare(const char* a, const char* b);
char*	get_input();
int		execute_command(t_cmd *cmd, int *exit_status);
void	child_work(t_cmd *cmd, int *fdr, int *fdw);
void	heredoc(t_red *red, t_hdoc *hdoc);
void	print_open_failing_reason(char *file);
void	change_args_with_exit_status(char **args, int exit_status);
void    execute(char *executable, char **arguments);

#endif

//type : > = 1 : >> = 2 : < = 3 : << : 4 