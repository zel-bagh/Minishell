/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:29:41 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/11/16 14:44:12 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Minishell.h"

int export(char **args, int input, int output, char **env)
{
    char a[5];

    args =0;
    a[4] = '\0';
    env = 0;
    read(input, a, 4);
    write(output, a, 5);
    return (0);
}

int call_func(char **args, int input, int output, char **env)
{
    if (ft_str_compare(args[0], "export"))
        return (export(args + 1, input, output, env));
   // if (ft_str_compare(args[0], "cd") || ft_str_compare(args[0], "CD"))
        //return (cd(args + 1, input, output));
   // if (ft_str_compare(args[0], "echo") || ft_str_compare(args[0], "ECHO"))
       // return (echo(args + 1, input, output));
       return (0);
}

int	get_input_output_from_red_l(t_red *red, int *input, int *output)
{
	int		i;
	t_hdoc	hdoc;
	int		index;

	i = -1;
	index = -1;
	heredoc(red, &hdoc);
	while (++i >= 0)
	{
		if (red->type == 3)
			index = i;
		if (red->type != 4)
		{
			if (check_file_error_l(red->file, hdoc, input, output))
				return (1);
			get_input_output(red, input, output);
		}
		if (errno)
			return (print_open_failing_reason_l(red->file, hdoc, input, output));
		if (red->next == NULL)
			break ;
		red = red->next;
	}
	setting_final_input(hdoc, index, input);
	return (0);
}

void    setting_input_output(int *in_out, t_cmd cmd, int *fdr, int *fdw)
{
    if (!in_out[0])
        if (cmd.prev)
            in_out[0] = fdr[0];
    if (!in_out[1])
    {
        if (cmd.next)
            in_out[1] = fdw[1];
        else
            in_out[1] = 1;
    }
}

int shell_builtin(t_cmd *cmd, int *fdr, int *fdw, char **env)
{
    int in_out[2];
    int in_out_backup[2];
    int func_ret;
    
    in_out[0] = 0;
    in_out[1] = 0;
    if (cmd->red)
        if (get_input_output_from_red_l(cmd->red, in_out, in_out + 1))
            return (1);
    in_out_backup[0] = in_out[0];
    in_out_backup[1] = in_out[1];
    setting_input_output(in_out, *cmd, fdr, fdw);
    func_ret = call_func(cmd->args, in_out[0], in_out[1], env);
    if (in_out_backup[0])
        close(in_out_backup[0]);
    if (in_out_backup[1])
        close(in_out_backup[1]);
     return (func_ret);
}