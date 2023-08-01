/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_draw_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:37:06 by arepsa            #+#    #+#             */
/*   Updated: 2023/07/31 15:37:10 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && y >= 0 && x < img->width && y < img->height)
	{
		pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)pixel = color;
	}
}

int	get_color(t_dot *a, t_dot *z)
{
	if (a->color != WHITE)
		return (a->color);
	else if (z->color != WHITE) 
	{
		return (z->color);
	}
	return (WHITE);
}
