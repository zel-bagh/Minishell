/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   managing_files_errors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:00:41 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/11/16 16:18:40 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

// {
// 		else
// 	{
// 		if (errno == 2)
// 		{
// 			printf("minishell: %s: No such file or directory\n", executable);
// 			exit(127);
// 		}
// 		else if (errno == 21)
// 		{
// 			if (*executable == '.' && *executable == '\0')
// 				printf("minishell: .: filename argument required\n.: usage: . filename [arguments]");
// 			else
// 				printf("minishell: %s: is a directory\n", executable);
// 			exit(126);
// 		}
// 		exit(-2);
// 	}
// }
void	print_open_failing_reason(char *file)
{
	if (errno == 2)
		printf("minishell: %s: No such file or directory\n", file);
	else if (errno == 21)
		printf("minishell: %s: is a directory\n", file);
	else if (errno == 13)
		printf("minishell: permission denied: %s\n", file);
	exit (1);
}

void    check_file_error(char *file)
{
    if(file[0] == '$' && ((file[1] >= 65 && file[1] <= 90) ||
     (file[1] >= 97 && file[1] <= 122) || file[1] == '-' ||
      (file[1] >= '0' && file[1] <= '9')))
    {
        printf("minishell: %s: ambiguous redirect", file);
        exit (1);
    }
}

int	print_open_failing_reason_l(char *file, t_hdoc hdoc, int *input, int *output)
{
	if (errno == 2)
		printf("minishell: %s: No such file or directory\n", file);
	else if (errno == 21)
		printf("minishell: %s: is a directory\n", file);
	else if (errno == 13)
		printf("minishell: permission denied: %s\n", file);
    if (hdoc.index >= 0)
        close(hdoc.heredoc_pipe_input_fd);
    if (*input != -1 && *input != 0)
        close(*input);
    if (*output != -1 && *output != 0)
        close(*output);
	return (1);
}

int check_file_error_l(char *file, t_hdoc hdoc, int *input, int *output)
{
    if(file[0] == '$' && ((file[1] >= 65 && file[1] <= 90) ||
     (file[1] >= 97 && file[1] <= 122) || file[1] == '-' ||
      (file[1] >= '0' && file[1] <= '9')))
    {
        printf("minishell: %s: ambiguous redirect\n", file);
        if (hdoc.index >= 0)
            printf("herdoc pipe has been closed\n");
        if (*input)
            close(*input);
        if (*output)
            close(*output);
        return (1);
    }
    return (0);
}