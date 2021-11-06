/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childprocess.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 09:14:09 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/11/06 16:12:25 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	open_files(t_red *red, int *input, int *output)
{
	int fd;
	
	if (red->type == 1)
		fd = open(red->file, O_CREAT | O_WRONLY | O_TRUNC , 0644);
	if (red->type == 2)
		fd = open(red->file, O_CREAT | O_WRONLY | O_APPEND , 0644);
	if (red->type == 3)
		fd = open(red->file, O_RDONLY);
	if (red->type == 1 || red->type == 2)
		*output = fd;
	if (red->type == 3)
		*input = fd;
}

void	get_input_output(t_red* red, int *input, int *output)
{
	if (red->type == 1 || red->type == 2)
	{
		if (*output)
			close(*output);
		open_files(red, input, output);
	}
	if (red->type == 3)
	{
		if (*input)
			close(*input);
		open_files(red, input, output);
	}
}

void	setting_final_input(t_hdoc hdoc, int index, int *input)
{
	if (hdoc.index == -1)
		return ;
	else if (index == -1)
		*input = hdoc.heredoc_pipe_input_fd;
	else if (index < hdoc.index)
		close (hdoc.heredoc_pipe_input_fd);
	else
	{
		close(*input);
		*input = hdoc.heredoc_pipe_input_fd;
	}
}

void	get_input_output_from_red(t_red *red, int *input, int *output)
{
	int		i;
	t_hdoc	hdoc;
	int		index;

	i = -1;
	errno = 0;
	index = -1;
	heredoc(red, &hdoc);
	while (++i >= 0)
	{
		if (red->type == 3)
			index = i;
		if (red->type != 4)
			get_input_output(red, input, output);
		if (errno)
			print_open_failing_reason(red->file, NULL);
		if (red->next == NULL)
			break ;
		red = red->next;
	}
	setting_final_input(hdoc, index, input);
}

void	child_work(t_cmd *cmd, int *fdr, int *fdw)
{
	int	input;
	int output;
	
	input = 0;
	output = 0;
	if (cmd->red)
		get_input_output_from_red(cmd->red, &input, &output);
	if(input)
		dup2(input, STDIN_FILENO);
	else
		if (cmd->prev != NULL)
			dup2(fdr[0], STDIN_FILENO);
	if(output)
		dup2(output, STDOUT_FILENO);
	else
		if (cmd->next != NULL)
			dup2(fdw[1], STDOUT_FILENO);
	errno = 0;
	check_executable(cmd->args[0]);
	execve(*cmd->args, cmd->args, NULL);
}