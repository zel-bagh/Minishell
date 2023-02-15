/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 19:52:22 by oidrissi          #+#    #+#             */
/*   Updated: 2021/11/27 02:52:03 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	free_red(t_red *red)
{
	t_red	*tmp;

	while (red)
	{
		free(red->name);
		tmp = red->next;
		free(red);
		red = tmp;
	}
}

void	free_g_sh(void)
{
	t_cmd	*cmd;

	cmd = g_sh;
	while (cmd)
	{
		free_args(cmd->args);
		free_red(cmd->red);
		g_sh = cmd->next;
		free(cmd);
		cmd = g_sh;
	}
	g_sh = NULL;
}

void	p_help(char *line)
{
	write(1, "syntax error\n", 13);
	free(line);
}

void	boucle(char *line, char **env, int exit_status)
{
	while (1)
	{
		line = readline("Sh> ");
		if (line == NULL)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		if (*line)
			add_history(line);
		line = trim_whitespaces(line);
		if (!parse(line))
		{
			p_help(line);
			continue ;
		}
		else if (parse(line) == 2)
			continue ;
		if (line)
		{
			g_sh = fill_sh(line, exit_status, env);
			execute_command(g_sh, &exit_status, &env, 0);
			free_g_sh();
		}
	}
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	int		exit_status;

	exit_status = 0;
	line = NULL;
	(void)av;
	if (ac != 1)
		return (0);
	ignctl();
	signal(SIGINT, handlesig);
	signal(SIGQUIT, SIG_IGN);
	change_env_to_heap(&env, 0, 0, -1);
	boucle(line, env, exit_status);
	return (0);
}
