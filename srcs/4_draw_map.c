/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_draw_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:36:19 by arepsa            #+#    #+#             */
/*   Updated: 2023/07/31 15:36:26 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_horizontal_lines(t_fdf *data, int x, int y)
{
	t_dot	a;
	t_dot	b;

	a.x = x;
	a.y = y;
	a.z = data->z_matrix[y][x].z;
	a.color = data->z_matrix[y][x].color;
	b.x = x + 1;
	b.y = y;
	b.z = data->z_matrix[y][x + 1].z;
	b.color = data->z_matrix[y][x + 1].color;
	draw_line(data, &a, &b);
}

static void	draw_vertical_lines(t_fdf *data, int x, int y)
{
	t_dot	a;
	t_dot	b;

	a.x = x;
	a.y = y;
	a.z = data->z_matrix[y][x].z;
	a.color = data->z_matrix[y][x].color;
	b.x = x;
	b.y = y + 1;
	b.z = data->z_matrix[y + 1][x].z;
	b.color = data->z_matrix[y + 1][x].color;
	draw_line(data, &a, &b);
}

void	draw_map(t_fdf *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (x < data->width - 1)
				draw_horizontal_lines(data, x, y);
			if (y < data->height - 1)
				draw_vertical_lines(data, x, y);
			x++;
		}
		free(data->z_matrix[y]);
		y++;
	}
	free(data->z_matrix);
}
