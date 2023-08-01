/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_transform_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:36:48 by arepsa            #+#    #+#             */
/*   Updated: 2023/07/31 15:36:53 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	isometric(t_dot *point)
{
	int	x_tmp;
	int	y_tmp;

	x_tmp = point->x;
	y_tmp = point->y;
	point->x = (x_tmp - y_tmp) * cos(0.523599);
	point->y = (x_tmp + y_tmp) * sin(0.523599) - point->z;
}

static void	scale_map(t_fdf *data, t_dot *a, t_dot *b)
{
	float	map_diagonal;
	float	factor;

	map_diagonal = sqrt(data->width * data->width \
						+ data->height * data->height);
	factor = 0.85 * HEIGHT / map_diagonal;
	a->x = round(a->x * factor);
	a->y = round(a->y * factor);
	b->x = round(b->x * factor);
	b->y = round(b->y * factor);
}

static void	center_map(t_dot *a, t_dot *b)
{
	int	x_offset;
	int	y_offset;

	x_offset = WIDTH * 2 / 5;
	y_offset = HEIGHT * 1 / 5;
	a->x += x_offset;
	a->y += y_offset;
	b->x += x_offset;
	b->y += y_offset;
}

void	transform_map(t_fdf *data, t_dot *a, t_dot *b)
{
	scale_map(data, a, b);
	isometric(a);
	isometric(b); 
	center_map(a, b);
}
