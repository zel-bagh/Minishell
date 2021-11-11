/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   managing_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:00:41 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/11/11 15:30:55 by zel-bagh         ###   ########.fr       */
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
        printf("minishell: %s: ambiguous redirect");
        exit (1);
    }
}