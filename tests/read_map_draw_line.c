/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:54:13 by arepsa            #+#    #+#             */
/*   Updated: 2023/06/20 13:55:29 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error(char *msg)
{
	ft_printf("Error : %s \n", msg);
	exit(EXIT_FAILURE);
}

int		get_height(char *file_name)
{
	int	fd;
	int	height;
	char *line;

	fd = open(file_name, O_RDONLY, 0);
	if (fd == -1)
        ft_error("Failed to open the file.");
	height = 0;
	while((line = get_next_line(fd)))
	{
		height++;
		free(line);
	}
	close(fd);
	return(height);

}

void	fill_matrix(int *z_line, char *line)
{
	char **numbers;
	int	i;

	numbers = ft_split(line, ' ');
	i = 0;
	while (numbers[i])
	{
		z_line[i] = ft_atoi(numbers[i]);
		free(numbers[i]);
		i++;	
	}
	free(numbers);
}

void	read_file(char *file_name, t_fdf *data)
{
	int	fd;
	char *line;
	int	i;
	int	width;

	data->height = get_height(file_name);
	data->z_matrix = (int **)malloc(sizeof(int *) * (data->height));
	fd = open (file_name, O_RDONLY, 0);
	if (fd == -1)
        ft_error("Failed to open the file.");
	i = 0;
	width = 0;
	while ((line = get_next_line(fd)))
	{
		if (width == 0)
			width = ft_count_words(line);
		data->z_matrix[i] = (int *)malloc(sizeof(int) * (width));
		fill_matrix(data->z_matrix[i], line);
		free(line);
		i++;
	}
	data->width = width;
	close(fd);
}

double	find_max(double a, double b)
{
	double	max;

	if (a > b)
		max = a;
	else
		max = b;
	return (max);
}

t_img	new_img(t_fdf new_win)
{
	t_img	img;

	img.img = mlx_new_image(new_win.mlx_ptr, new_win.width, new_win.height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length,
								&img.endian);
	img.width = new_win.width;
	img.height = new_win.height;
	return (img);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && y >= 0 && x < img->width && y < img->height)
	{
		pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int*)pixel = color;
	}
}

void	draw_line(t_img *img, float x, float y, float x1, float y1)
{
	float x_step;
	float y_step;
	int	max;

	x_step = x1 - x;
	y_step = y1 - y;
	max = find_max(fabs(x_step), fabs(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(x - x1) || (int)(y - y1))
	{
		put_pixel(img, x, y, WHITE);
		x += x_step;
		y += y_step;
	}

}
t_fdf	new_program(int w, int h, char *str)
{
	t_fdf fdf;

	fdf.mlx_ptr = mlx_init();
	fdf.width = w;
	fdf.height = h;
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, w, h, str);
	return (fdf);
}
int	exit_window(t_fdf *win)
{
	if (win)
	{
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
		free(win->mlx_ptr);
		exit (EXIT_SUCCESS);
	}
	return (0);
}
int	main(int argc, char **argv)
{
	t_fdf	*data;

	if (argc != 2)
		ft_error("Invalid input\nValid input:\n./fdf <filename.fdf>");
	data = (t_fdf*)malloc(sizeof(t_fdf));
	read_file(argv[1], data);
	*data = new_program(WIDTH, HEIGHT, "fdf");
	if (!data->mlx_ptr || !data->win_ptr)
		return (1);
	data->img = new_img(*data);
	draw_line(&(data->img), 10, 10, 110, 110);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	mlx_hook(data->win_ptr, 17, 0, exit_window, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
