/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:12:19 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/10/18 20:51:44 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	close_fd(t_cmd *next, int *fdr, int *fdw)
{
	close(fdr[0]);
	if(next == NULL)
	{
		close(fdw[1]);
		close(fdw[0]);
		return(0);
	}
	fdr[0] = fdw[0];
	fdr[1] = fdw[1];
	return(1);
}

void	get_input_output(t_red *red)
{
	int input;
	int output;
	
	input = 0;
	output = 0;
	while (1)
	{
		if (red->type == 1)
			output = open(red->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (red->type == 2)
			output = open(red->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (red->type == 3)
			input = open(red->file, O_RDONLY);
		if (red->next == NULL)
			break ;
		red = red->next;
	}
	if (input && output)
	{
		dup2(1, output);
		dup2(0, input);
	}
}

void	child_work(t_cmd *cmd, int *fdr, int *fdw)
{
	if(cmd->prev != NULL)
		dup2(fdr[0], STDIN_FILENO);
	if(cmd->next != NULL)
		dup2(fdw[1], STDOUT_FILENO);
	get_input_output(cmd->red);
	execve(*cmd->args, cmd->args + 1, NULL);
}
void	execute_command(t_cmd *cmd)
{
	int id;
	int status;
	int fdr[2];
	int	fdw[2];

	pipe(fdw);
	pipe(fdr);
	while(1)
	{
		close(fdr[1]);
		id = fork();
		
		if (id == 0)
			child_work(cmd, fdr, fdw);

		wait(&status);
		if(close_fd(cmd->next, fdr, fdw) == 0)
			break;
		pipe(fdw);
		cmd = cmd->next;
	}
}

int		main()
{
	int i;
	t_cmd	*cmd;

	cmd = malloc(3*sizeof(t_cmd));
	//i = -1;
	cmd->args = malloc(4*sizeof(char*));
	cmd->args[0]= "/bin/ls";
	cmd->args[1]= "ls";
	cmd->args[2]= NULL;
	cmd->args[3]= NULL;
	cmd->next = cmd + 1;
	
	(cmd+1)->args = malloc(4*sizeof(char*));
	(cmd+1)->args[0]= "/usr/bin/grep";
	(cmd+1)->args[1]= "grep";
	(cmd+1)->args[2]= "Mini";
	(cmd+1)->args[3]= NULL;
	(cmd+1)->next = NULL;

	
	(cmd+2)->args = malloc(4*sizeof(char*));
	(cmd+2)->args[0]= "/usr/bin/wc";
	(cmd+2)->args[1]= "wc";
	(cmd+2)->args[2]= NULL;
	(cmd+2)->args[3]= NULL;
	(cmd+2)->next = NULL;
	execute_command(cmd);
}