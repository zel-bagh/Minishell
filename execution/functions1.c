/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:46:23 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/12/03 23:50:32 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "Minishell.h"

int	ft_str_compare(const char *a, const char *b)
{
	int	i;

	if (a == NULL || b == NULL)
		return (2);
	i = 0;
	while (a[i] != '\0' || b[i] != '\0')
	{
		if (a[i] != b[i])
			return (0);
		i++;
	}
	return (1);
}

void	less_lines1(int *d)
{
	signal(SIGINT, handlesig3);
	signal(SIGQUIT, handlesig2);
	*d = fork();
}

void	less_lines2(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handlesig);
}
