/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_out_of_local_func.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 09:14:09 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/11/13 10:42:38 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	get_input_output_from_red_l(t_red *red, int *input, int *output)
{
	int		i;
	t_hdoc	hdoc;
	int		index;

	i = -1;
	index = -1;
	heredoc(red, &hdoc);
	errno = 0;
	while (++i >= 0)
	{
		if (red->type == 3)
			index = i;
		if (red->type != 4)
		{
			if (check_file_error_l(red->file, hdoc, &input, &output))
				return (1);
			get_input_output(red, input, output);
		}
		if (errno)
			if (print_open_failing_reason_l(red->file, hdoc, &input, &output))
				return (1);
		if (red->next == NULL)
			break ;
		red = red->next;
	}
	setting_final_input(hdoc, index, input);
}