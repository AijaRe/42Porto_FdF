/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:55:41 by arepsa            #+#    #+#             */
/*   Updated: 2023/05/22 12:13:36 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*Store in the static variable the leftover after extracting the line:
*	locate '\n', pass one index further and copy up to the '\0'*/
static char	*get_remainder(char *str)
{
	char	*remainder;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0' || str[i + 1] == '\0')
	{
		free(str);
		return (NULL);
	}
	remainder = malloc(sizeof(char) * (ft_strlen_gnl(str) - i + 1));
	if (!remainder)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		remainder[j++] = str[i++];
	remainder[j] = '\0';
	free(str);
	return (remainder);
}

/*	Extract the line (ending in either '\n' and `\0` or only `\0`)
*	from static variable.
*	Return the string ending in a line break (`\n` + `\0`).*/
static char	*trim_new_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

/*	Accumulate buffer results into a static string.
*	Includes '\n' and whatever comes next up to buffer size.
*	Allocate buffer dynamically to tackle big buffer sizes.*/
static char	*get_full_line(int fd, char *str)
{
	char	*buff;
	int		bytes_read;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr_gnl(str, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buff);
			free(str);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		str = ft_strjoin_gnl(str, buff);
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = get_full_line(fd, str);
	if (!str)
		return (NULL);
	line = trim_new_line(str);
	str = get_remainder(str);
	return (line);
}
/*
int	main()
{
int		fd;
int		i;
char	*line;
char	*file = "short_poem";

fd = open(file,  O_RDONLY);
if (fd == -1)
{
	printf("Error opening file.\n");
	return (1);
}
i = 1;
while (i < 15)
{
	line = get_next_line(fd);
	printf("Line%d: %s\n", i, line);
	free(line);
	i++;
}
close(fd);
return (0);
}*/
