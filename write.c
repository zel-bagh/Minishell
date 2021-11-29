/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:58:24 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/11/29 11:40:00 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"Minishell.h"




int main(int argc, char **argv, char **env)
{
	// int		id;
    // int     exit_status;

    // id = fork();
    // if (id == 0)
    // {
    //     printf("hi\n");
    //     exit(1);
    // }
    // waitpid(id, &exit_status, 0);
    // printf("exit_status is = %d\n", exit_status);
    int a = -4;
    if ((unsigned char)a == 252)
    return 1; 
    unsigned char b = a;
    unsigned char c = 252;
    if (b == c)
        printf("hi\n");
}
