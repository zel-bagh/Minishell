/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 09:12:37 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/11/06 12:13:35 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	print_open_failing_reason(t_red *red)
{
	if (errno == 2)
		printf("minishell: %s: No such file or directory\n", red->file);
}

int	close_fd_pipes(t_cmd *next, int *fdr, int *fdw, int id)
{
	int status;
	
	close(fdr[0]);
	if(next == NULL)
	{
		close(fdw[1]);
		close(fdw[0]);
		waitpid(id, &status, 0);
		while(wait(NULL) != -1)
			continue;
		return(0);
	}
	fdr[0] = fdw[0];
	fdr[1] = fdw[1];
	return(1);
}

void	execute_command(t_cmd *cmd)
{
	int id;
	int fdr[2];
	int	fdw[2];

	pipe(fdw);
	while(1)
	{
		id = fork();	
		if (id == 0)
			child_work(cmd, fdr, fdw);
		else
		{
			if(close_fd_pipes(cmd->next, fdr, fdw, id) == 0)
				break ;
			close(fdr[1]);
			pipe(fdw);
			cmd = cmd->next;
		}
	}
}
