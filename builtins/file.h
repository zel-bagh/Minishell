/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 16:58:17 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/10/16 17:00:24 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int	ft_strlen(const char *a);
char*	ft_strjoin(const char *a, const char *b);
int	ft_str_compare(const char* a, const char* b);
char*   get_input();


#endif