/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:12:19 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/10/19 21:38:02 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	print_open_failing_reason(t_red *red)
{
	if (errno == 2)
		printf("minishell: %s: No such file or directory\n", red->file);
}

int	close_fd_pipes(t_cmd *next, int *fdr, int *fdw)
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
void	open_files(t_red *red, int *input, int *output)
{
	int fd;
	
	if(red->type == 1)
		fd = open(red->file, O_CREAT | O_WRONLY | O_TRUNC , 0644);
	if(red->type == 2)
		fd = open(red->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if(red->type == 3)
		fd = open(red->file, O_RDONLY);
	if(red->type == 1 || red->type == 2)
		*output = fd;
	if(red->type == 3 || red->type == 4)
		*input = fd;
}

void	get_input_output_from_red(t_red *red, int *input, int *output)
{
	errno = 0;
	while (1)
	{
		if (red->type == 1 || red->type == 2)
		{
			if (*output)
				close(*output);
			open_files(red,input, output);

		}
		if (red->type == 3 || red->type == 4)
		{   
			if (*input)
				close(*input);
			open_files(red,input, output);
		}
		if (errno)
		{
			print_open_failing_reason(red);
			exit(0);
		}
		if (red->next == NULL)
			break ;
		red = red->next;
	}
}

void	child_work(t_cmd *cmd, int *fdr, int *fdw)
{
	int	input;
	int output;
	
	input = 0;
	output = 0;
	if (cmd->red)
		get_input_output_from_red(cmd->red, &input, &output);
	if(input)
		dup2(input, STDIN_FILENO);
	else
		if (cmd->prev != NULL)
			dup2(fdr[0], STDIN_FILENO);
	if(output)
		dup2(output, STDOUT_FILENO);
	else
		if (cmd->next != NULL)
			dup2(fdw[1], STDOUT_FILENO);
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
		if(close_fd_pipes(cmd->next, fdr, fdw) == 0)
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
	cmd->args = malloc(4*sizeof(char*));
	cmd->args[0]= "/bin/ls";
	cmd->args[1]= "ls";
	cmd->args[2]= NULL;
	cmd->args[3]= NULL;
	cmd->next = cmd + 1;
	cmd->red =NULL;

	(cmd+1)->args = malloc(4*sizeof(char*));
	(cmd+1)->args[0]= "/usr/bin/grep";
	(cmd+1)->args[1]= "grep";
	(cmd+1)->args[2]= "inc";
	(cmd+1)->args[3]= NULL;
	(cmd+1)->prev = cmd ;
	(cmd+1)->red = malloc(4 * sizeof(t_red));
	{
		(cmd+1)->red->file = "tests.c";
		(cmd+1)->red->type = 1;
		(cmd+1)->red->next = (cmd+1)->red+1;
		
(cmd+1)->red = (cmd+1)->red + 1;
		(cmd+1)->red->file = "yowaimo";
		(cmd+1)->red->type = 3;
		(cmd+1)->red->next = NULL;//(cmd+1)->red+1;
		

// (cmd+1)->red = (cmd+1)->red + 1;
// 		(cmd+1)->red->file = "yo.c";
// 		(cmd+1)->red->type = 1;
// 		(cmd+1)->red->next = NULL;
		
		// (cmd+1)->red = (cmd+1)->red - 3;
		
	}
	 (cmd+1)->next = cmd + 2;

	
	(cmd+2)->args = malloc(4*sizeof(char*));
	(cmd+2)->args[0]= "/usr/bin/wc";
	(cmd+2)->args[1]= "wc";
	(cmd+2)->args[2]= NULL;
	(cmd+2)->args[3]= NULL;
	(cmd+2)->next = NULL;
	(cmd+2)->red = NULL;
	(cmd+2)->prev = cmd + 1;

	execute_command(cmd);
}