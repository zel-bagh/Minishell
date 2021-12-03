/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 22:46:09 by oidrissi          #+#    #+#             */
/*   Updated: 2021/12/03 23:34:49 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handlesig(int i)
{
	i = 0;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ignctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	handlesig3(int i)
{
	i = 0;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	handlesig2(int i)
{
	i = 0;
	write(1, "Quit: 3\n", 8);
}
