/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 10:14:26 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/10/18 18:09:29 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
int	function(void)
{
	return (0);
}

int	main(int argc, char **argv)
{
	int		fd[2];
	int		k[2];
	char	a[100];
	int		fd0;
	int		fd1;

	pipe(k);
	fd0 = 36;
	write(k[1], &fd0, 4);
	fd0 = 4;
	write(k[1], &fd0, 4);
	write(1, k[0], )
	
	printf("yo it has passed");
}
