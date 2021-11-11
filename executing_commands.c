/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 09:12:37 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/11/11 14:00:38 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

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

int	execute_command(t_cmd *cmd, int *exit_status)
{
	int			id;
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
				waitpid(id, exit_status, 0);
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
