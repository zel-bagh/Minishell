/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:58:24 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/11/25 16:42:27 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int    check_argFor_unset(char *args, int *k)
{
    int j;

    j = -1;
    while (args[j++])
    {
        if ((j == 0 && args[j] >= 48 && args[j] <= 57) || ((
         args[j] < 48 || args[j] > 57) && (args[j] < 65
        || args[j] > 90) && (args[j] < 97 || args[j] > 122)
         && args[j] != '_'))
        {
            printf("Minishell: unset: `%s': not a valid identifier\n", args);
            *k = 1;
            return (0);
        }
    }
    return (1);
}
int	main(int argc, char **argv, char **env)
{
	int		id;
	char	*c;
    char    *b;

    printf("%d\n", check_argFor_unset("=", &id));
}
