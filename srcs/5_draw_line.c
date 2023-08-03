/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_draw_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:36:33 by arepsa            #+#    #+#             */
/*   Updated: 2023/07/31 15:36:40 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Set the starting point and decide weather to increment or decrement
* each axis, based on difference between starting and ending points*/
static void	bresenham_define(t_bresenham *param, t_dot *a, t_dot *b)
{
	param->dx = abs(b->x - a->x);
	param->dy = -1 * abs(b->y - a->y);
	if (a->x <= b->x)
		param->sx = 1;
	else
		param->sx = -1;
	if (a->y <= b->y)
		param->sy = 1;
	else
		param->sy = -1;
	param->err = param->dx + param->dy;
	param->x0 = a->x;
	param->y0 = a->y;
}

/* Check if the current point is within image boundaries
* Check if we have reached the end point
* Increment or decrement x and y coordinates based on error parameter*/
void	draw_line(t_fdf *data, t_dot *a, t_dot *b)
{
	t_bresenham	param;

	transform_map(data, a, b);
	bresenham_define(&param, a, b);
	while (1)
	{
		if (param.x0 < WIDTH && param.x0 > 0
			&& param.y0 < HEIGHT && param.y0 > 0)
			put_pixel(&data->img, param.x0, param.y0, get_color(a, b));
		if (param.x0 == b->x && param.y0 == b->y)
			break ;
		if (2 * param.err >= param.dy && param.x0 != b->x)
		{
			param.err += param.dy;
			param.x0 += param.sx;
		}
		if (2 * param.err <= param.dx && param.y0 != b->y)
		{
			param.err += param.dx;
			param.y0 += param.sy;
		}
	}
}
