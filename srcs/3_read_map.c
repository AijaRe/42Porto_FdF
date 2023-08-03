/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_read_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:35:54 by arepsa            #+#    #+#             */
/*   Updated: 2023/07/31 15:36:03 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_height(char *file_name)
{
	int		fd;
	int		height;
	char	*line;

	height = 0;
	fd = open(file_name, O_RDONLY, 0);
	line = NULL;
	if (fd == -1)
		ft_error("Failed to open the file.");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		height++;
		free(line);
	}
	close(fd);
	return (height);
}

static void	split_line(t_dot *matrix, char *line)
{
	char	**points;
	int		i;

	points = ft_split(line, ' ');
	i = 0;
	while (points[i])
	{
		matrix[i].z = ft_atoi(points[i]);
		matrix[i].x = 0;
		matrix[i].y = 0;
		if (!ft_strchr(points[i], ','))
			matrix[i].color = WHITE;
		else
		{
			matrix[i].color = ft_atoi_hex(ft_strchr(points[i], ',') + 3);
		}
		i++;
	}
	free_tab(points);
}

/*copy map data into char arry*/
void	get_map(t_fdf *data, char *file_name)
{
	int	fd;
	int	i;

	i = 0;
	data->height = get_height(file_name);
	data->map = malloc(sizeof(char *) * (data->height + 1));
	if (!data->map)
		ft_error("Memory allocation failed for char array map.");
	fd = open (file_name, O_RDONLY, 0);
	if (fd == -1)
	{
		ft_error("Failed to open the file.");
	}
	data->map[0] = get_next_line(fd);
	while (data->map[i])
	{
		data->map[++i] = get_next_line(fd);
	}
	close(fd);
}

/*transfer char array line by line into t_dot matrix*/
void	read_file(t_fdf *data)
{
	int	i;
	int	prev_width;
	int	curr_width;

	data->z_matrix = (t_dot **)malloc(sizeof(t_dot *) * data->height);
	if (!data->z_matrix)
		ft_error("Memory allocation failed for t_dot matrix.");
	i = 0;
	curr_width = 0;
	prev_width = 0;
	while ((data->map[i]))
	{
		curr_width = ft_count_words(data->map[i]);
		if (prev_width == 0)
			prev_width = curr_width;
		else if (curr_width != prev_width)
			ft_map_error(data, i - 1, "Invalid map: different size rows.");
		data->z_matrix[i] = (t_dot *)malloc(sizeof(t_dot) * curr_width);
		if (!data->z_matrix[i])
			ft_map_error(data, i, "Memory allocation failed for t_dot line");
		split_line(data->z_matrix[i], data->map[i]);
		i++;
	}
	free_tab(data->map);
	data->width = curr_width;
}
