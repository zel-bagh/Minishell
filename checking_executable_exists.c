/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_executable_exists.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 13:48:32 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/11/07 14:09:24 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void    execute_2()
{
    if (errno == 13)
    {
        printf("minishell: %s: Permission denied");
        exit(126);
    }
    if (errno == 2)
    {
        printf("minishell: %s: No such file or directory");
        exit(127);
    }
    exit(-4);
}

void    execute(char *executable, char **arguments)
{
    int i;
    int fd;
    
    i = -1;
    errno = 0;
    while (executable[++i])
        if (executable[i] == '/')
            break;
    if (executable[i] == '/')
    {
        fd = open(executable, O_WRONLY);
        if (errno == 21)
        {
            printf("minishell: %s: is a directory");
            exit(126);
        }
        close(fd);
        errno = 0;
        execve(executable, arguments, NULL);
        execute_2();
    }
    else
     while(1)
        continue; //
}