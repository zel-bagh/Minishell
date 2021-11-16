/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:12:19 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/11/16 16:55:30 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int		main(int argc, char **argv, char **env)
{
	t_cmd	*cmd;
	int		exit_status;
	argc = 1;
	argv = 0;

	cmd = malloc(3*sizeof(t_cmd));
	cmd->args = malloc(4*sizeof(char*));
	cmd->args[0]= "export";
	cmd->args[1]= NULL;
	cmd->args[2]= NULL;
	cmd->args[3]= NULL;
	cmd->next = NULL;//cmd + 1;
	cmd->prev = NULL;
	cmd->red = malloc(4 * sizeof(t_red));
{{
		
		(cmd)->red->file = "write.c";
		(cmd)->red->type = 3;
		(cmd)->red->next =(cmd)->red+1;
		
(cmd)->red = (cmd)->red + 1;
		(cmd)->red->file = "yo.c";
		(cmd)->red->type = 2;
		(cmd)->red->next = NULL;//(cmd)->red+1;
		

(cmd)->red = (cmd)->red + 1;
		(cmd)->red->file = "/stop";
		(cmd)->red->type = 2;
		(cmd)->red->next = (cmd)->red+1;

(cmd)->red = (cmd)->red + 1;
		(cmd)->red->file = "yo.c";
		(cmd)->red->type = 3;
		(cmd)->red->next = NULL;
		
 		(cmd)->red = (cmd)->red - 3;	
}}



	(cmd+1)->args = malloc(4*sizeof(char*));
	(cmd+1)->args[0]= "/usr/bin/wc";
	(cmd+1)->args[1]= NULL;
	(cmd+1)->args[2]= NULL;
	(cmd+1)->args[3]= NULL;
	(cmd+1)->prev = cmd ;
	(cmd+1)->red = malloc(4 * sizeof(t_red));
	
	{{
		(cmd+1)->red->file = "yo.c";
		(cmd+1)->red->type = 3;
		(cmd+1)->red->next = (cmd+1)->red+1;
		
(cmd+1)->red = (cmd+1)->red + 1;
		(cmd+1)->red->file = "Miasdfafaasddadadsasll.c";
		(cmd+1)->red->type = 2;
		(cmd+1)->red->next = (cmd+1)->red+1;
		

(cmd+1)->red = (cmd+1)->red + 1;
		(cmd+1)->red->file = "yko.c";
		(cmd+1)->red->type = 3;
		(cmd+1)->red->next = NULL;
		
 		(cmd+1)->red = (cmd+1)->red - 2;
 	
	 
	}}
	(cmd+1)->next = cmd + 2;


	(cmd+2)->args = malloc(4*sizeof(char*));
	(cmd+2)->args[0]= "/bin/echo";
	(cmd+2)->args[1]= ":)";
	(cmd+2)->args[2]= NULL;
	(cmd+2)->args[3]= NULL;
	(cmd+2)->next = NULL;
	(cmd+2)->red = NULL;
	(cmd+2)->prev = cmd + 1;

	execute_command(cmd, &exit_status, env);
	printf("exit status is %d\n", exit_status);
}