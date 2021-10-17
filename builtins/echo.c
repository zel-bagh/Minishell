/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 10:57:05 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/10/16 17:00:48 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

void	ft_write(int i, int n, char **argv)
{
	while (n-- > 0)
	{
		printf("%s", argv[i++]);
		if (n != 0)
			printf(" ");
	}
}

int	main(int argc, char **argv)
{
	int	i;

	i = 2;
	if (argc == 1)
		printf("\n");
	else
	{
		if (ft_str_compare(argv[1], "-n"))
			ft_write(2, argc - 2, argv);
		else
		{
			ft_write(1, argc - 1, argv);
			printf("\n");
		}
	}
}