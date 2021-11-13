/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:29:41 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/11/13 12:22:51 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Minishell.h"

int check_if_exctble_is_here(t_cmd *cmd, int *fdr, int *fdw, int *fnc_exit)
{
    int input;
    int output;
    int input_backup;
    int output_backup;
    
    input = 0;
    output = 0;
    if (ft_str_compare(cmd->args[0], "export") || ft_str_compare(cmd->args[0], "cd"))
    {
        if (cmd->red)
            if(get_input_output_from_red_l(cmd->red, &input, &output))
                return ((fnc_exit = 1) == 1);
        input_backup = input;
        output_backup = output;
        if (!input)
            input = fdr[0];
        if (!output)
            output = fdw[1];
        call_func(cmd->args, input, output, fnc_exit);
        if (input_backup)
            close(input_backup);
        if (output_backup)
            close(output_backup);
        return (1);
    }
    return (0);
}