/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_executable_exists.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 13:48:32 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/11/06 16:47:41 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

include "Minishell.h"

void    check_executable(char *exec)
{
    int i;
    int fd;

    i = -1;
    while (exec[++i])
        if (exec[i] == '/')
            break;
    if (exec[i] == '/')
    {
        fd = open(exec, O_WRONLY);
        if (fd == -1)
            print_open_failing_reason(NULL, exec);
        close(fd);
    }
    //ELSE
}