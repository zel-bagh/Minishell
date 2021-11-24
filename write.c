/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:58:24 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/11/24 16:49:19 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int    compaire_arg_env(char *argument, char *env)
{
    int j;
    int k;

    j = -1;
    k = -1;
    while (env[++j] != '=' && env[j] && argument[++k] != '=' && argument[k])
        if (env[j] != argument[k])
            break ;
    if ((!env[j] || env[j] == '=') && (!argument[j] || argument[j] == '='))
    {
        if (argument[j] == '=')
            return (2);
        return (1);
    }
    return (0);
}

int	func(void)
{
	return (3);
}

int	fun(int i)
{
	return (i);
}

int	main(int argc, char **argv, char **env)
{
	int		id;
	char	*c;
    char    *b;

	//id = fun(func());
	//c = id + 48;
	//write(1, &c, 1);
    c = malloc(1 * sizeof(char *));
    b = malloc(1 * sizeof(char *));
    free (c);
    *b = 'a';
	printf("%c\n", *b);
}
