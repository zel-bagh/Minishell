/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 09:12:37 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/11/06 16:38:24 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	print_open_failing_reason(char *red, char *executable)
{
	if (red)
	{
		if (errno == 2)
		{
			printf("minishell: %s: No such file or directory\n", red);
			exit(1);
		}
		else if (errno == 21)
		{
			printf("minishell: %s: is a directory\n", red);
			exit(1);
		}
		exit(-1);
	}
	else
	{
		if (errno == 2)
		{
			printf("minishell: %s: No such file or directory\n", executable);
			exit(127);
		}
		else if (errno == 21)
		{
			if (*executable == '.' && *executable == '\0')
				printf("minishell: .: filename argument required\n.: usage: . filename [arguments]");
			else
				printf("minishell: %s: is a directory\n", executable);
			exit(126);
		}
		exit(-2);
	}
}

int	close_fd_pipes(t_cmd *next, int *fdr, int *fdw)
{	
	close(fdr[0]);
	if(next == NULL)
	{
		close(fdw[1]);
		close(fdw[0]);
		return(1);
	}
	fdr[0] = fdw[0];
	fdr[1] = fdw[1];
	return(0);
}

int	execute_command(t_cmd *cmd)
{
	int			id;
	static int	exit_status;
	int			fdr[2];
	int			fdw[2];

	pipe(fdw);
	while(1)
	{
		id = fork();	
		if (id == 0)
			child_work(cmd, fdr, fdw);
		else
		{
			if (close_fd_pipes(cmd->next, fdr, fdw))
			{
				waitpid(id, &exit_status, 0);
				while(wait(NULL) != -1)
					continue;
				break ;
			}
			close(fdr[1]);
			pipe(fdw);
			cmd = cmd->next;
		}
	}
}
