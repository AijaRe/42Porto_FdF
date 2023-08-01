/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:54:13 by arepsa            #+#    #+#             */
/*   Updated: 2023/06/20 13:55:29 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_img	new_img(t_fdf data)
{
	t_img	img;

	img.img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	if (img.img == NULL)
		ft_error("Failed to create image.");
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, \
									&img.endian);
	img.width = WIDTH;
	img.height = HEIGHT;
	return (img);
}

t_fdf	new_program(int w, int h, char *str)
{
	t_fdf	fdf;

	fdf.mlx_ptr = mlx_init();
	fdf.width = w;
	fdf.height = h;
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, WIDTH, HEIGHT, str);
	return (fdf);
}

int	exit_window(t_fdf *win)
{
	if (win)
	{
		mlx_destroy_image(win->mlx_ptr, win->img.img);
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
		mlx_destroy_display(win->mlx_ptr);
		free(win->mlx_ptr);
		free(win);
		exit (EXIT_SUCCESS);
	}
	return (0);
}

int	handle_key_event(int key_pressed, void	*param)
{
	t_fdf	*win;

	win = (t_fdf *)param;
	if (key_pressed == ESC || !win)
		exit_window(win);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	*data;

	handle_input_errors(argc, argv[1]);
	data = (t_fdf *)malloc(sizeof(t_fdf));
	get_map(data, argv[1]);
	read_file(data);
	*data = new_program(data->width, data->height, "fdf");
	if (!data->mlx_ptr || !data->win_ptr)
		return (1);
	data->img = new_img(*data);
	draw_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	mlx_hook(data->win_ptr, 17, 0, exit_window, data);
	mlx_key_hook(data->win_ptr, &handle_key_event, data);
	mlx_loop(data->mlx_ptr);
	free(data);
	exit(EXIT_SUCCESS);
}
