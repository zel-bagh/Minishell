/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 09:12:37 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/10/24 10:38:31 by zel-bagh         ###   ########.fr       */
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
			break ;
		pipe(fdw);
		cmd = cmd->next;
	}
}
