/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:58:24 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/11/22 19:17:26 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int	func(void)
{
	return (3);
}

int	fun(int i)
{
	return (i);
}

int	main(void)
{
	int		id;
	char	c;

	id = fun(func());
	c = id + 48;
	write(1, &c, 1);
}
