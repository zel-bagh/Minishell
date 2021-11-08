/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chnage_dollar_with_last_exit_status.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 11:08:10 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/11/08 12:05:03 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Minishell.h"

char    *ft_itoa(int i)
{
    int counter;
    int save;
    char *string;

    save = i;
    counter = 1;
    while (i / 10 != 0)
    {
        counter++;
        i = i / 10;
    }
    string = malloc((counter + 1) * sizeof(char));
    string[counter] = '\0';
    string = string + counter - 1;
    while(save / 10 != 0)
    {
        *string = (save % 10) + 48;
        save = save / 10;
        string--;
    }
    *string = save + 48;
    return (string);
}

void	change_args_with_exit_status(char **args, int exit_status)
{
    int     i;
    char    *status;
    int     d;

    i = -1;
    d = 0;
    status = ft_itoa(exit_status);
    while(args[++i] != NULL)
    {
        if (ft_str_compare(args[i], "$?"))
        {
            args[i] = status;
            d = 1;
        }
    }
    if (d = 0)
        free(status);
}