/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 09:12:37 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/11/16 09:53:21 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	wait_for_children(int id, int *exit_status, char *exec)
{
	if (ft_str_compare(exec, "export") ||
    ft_str_compare(exec, "cd") || ft_str_compare(exec, "echo")
     || ft_str_compare(exec, "CD") ||
      ft_str_compare(exec, "ECHO"))
		*exit_status = *exit_status;
	else
		waitpid(id, exit_status, 0);
	while(wait(NULL) != -1)
		continue;
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
	close(fdr[1]);
	return(0);
}

int	check_if_shell_builtin(char *exec)
{
	if (ft_str_compare(exec, "export") ||
    ft_str_compare(exec, "cd") || ft_str_compare(exec, "echo")
     || ft_str_compare(exec, "CD") ||
      ft_str_compare(exec, "ECHO"))
	  return (1);
	return (0);
}

void	execute_command(t_cmd *cmd, int *exit_status, char **env)
{
	int			id;
	int			fdr[2];
	int			fdw[2];

	pipe(fdw);
	while(1)
	{
		if (check_if_shell_builtin(cmd->args[0]))
			*exit_status = shell_builtin(cmd, fdr, fdw, env);
		else
		{
			id = fork();	
			if (id == 0)
				child_work(cmd, fdr, fdw);
		}
		if (close_fd_pipes(cmd->next, fdr, fdw))
		{
			wait_for_children(id, exit_status, cmd->args[0]);
			break ;
		}
		pipe(fdw);
		cmd = cmd->next;
	}
}
