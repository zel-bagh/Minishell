/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bagh <zel-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:46:23 by zel-bagh          #+#    #+#             */
/*   Updated: 2021/11/30 18:02:18 by zel-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(const char *a)
{
	int	n;

	n = 0;
	while (a[n] != '\0')
		n++;
	return (n);
}

char	*ft_strjoin(const char *a, const char *b)
{
	char	*new;
	int		i;
	int		j;

	if (a == NULL || b == NULL)
		return (NULL);
	new = malloc(ft_strlen(a) + ft_strlen(b) + 1);
	i = -1;
	while (a[++i] != '\0')
		new[i] = a[i];
	i--;
	j = -1;
	while (b[++j] != '\0')
		new[++i] = b[j];
	new[++i] = '\0';
	return (new);
}

int	ft_str_compare(const char *a, const char *b)
{
	int	i;

	if (a == NULL || b == NULL)
		return (2);
	i = 0;
	while (a[i] != '\0' || b[i] != '\0')
	{
		if (a[i] != b[i])
			return (0);
		i++;
	}
	return (1);
}

char	*get_input(void)
{
	char	*text;
	char	*buffer;
	int		r;
	char	*tmp;

	text = malloc(sizeof(char));
	buffer = malloc(9 * sizeof(char));
	text[0] = '\0';
	while (1)
	{
		r = read(0, buffer, 8);
		buffer[r] = '\0';
		if (r == 0)
		{
			free(buffer);
			return (text);
		}
		tmp = text;
		text = ft_strjoin(text, buffer);
		free(tmp);
	}
}
