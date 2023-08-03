/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:56:10 by arepsa            #+#    #+#             */
/*   Updated: 2023/05/18 14:56:14 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr_gnl(char *s, int c)
{
	char	ch;

	ch = (char)c;
	if (!s)
		return (0);
	while (*s != '\0' && *s != ch)
		s++;
	if (*s == ch)
		return (s);
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*joined;
	int		i;
	int		j;

	i = -1;
	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	joined = (char *)malloc(sizeof(char) * \
		(ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1));
	if (!joined)
		return (NULL);
	while (s1[++i] != '\0')
		joined[i] = s1[i];
	j = 0;
	while (s2[j] != '\0')
		joined[i++] = s2[j++];
	joined[i++] = '\0';
	free(s1);
	return (joined);
}
