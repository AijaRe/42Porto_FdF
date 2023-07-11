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
	printf("Data height: %d\n", data->height);
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
	printf("Data width: %d\n", width);
	close(fd);
}

int	find_max(int a, int b)
{
	int	max;

	if (a > b)
		max = a;
	else
		max = b;
	return (max);
}

t_img	new_img(t_fdf data)
{
	t_img	img;

	img.img = mlx_new_image(data.mlx_ptr, data.width * SIZE, data.height * SIZE);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length,
								&img.endian);
	img.width = data.width * SIZE;
	img.height = data.height * SIZE;
	printf("Img width: %d\n", img.width);
	printf("Img height: %d\n", img.height);
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

void	isometric(int *x, int *y, int z)
{
	float	x_tmp;
	float	y_tmp;

	x_tmp = *x;
	y_tmp = *y;
	*x = (x_tmp - y_tmp) * cos(0.523599);
	*y = (x_tmp + y_tmp) * sin(0.523599) - z;

}

void	draw_line(t_fdf *data, int x, int y, int x1, int y1)
{
	int x_step;
	int y_step;
	int	max;
	int z;
	int z1;

	z = data->z_matrix[y][x];
	z1 = data->z_matrix[y1][x1];

	x *= SPACE;
	y *= SPACE;
	x1 *= SPACE;
	y1 *= SPACE;
	x_step = x1 - x;
	y_step = y1 - y;
	printf("Before iso: (x:%d y:%d)\n", x, y);
	printf("Before iso: (x1:%d y1:%d)\n", x1, y1);
	isometric(&x, &y, z);
	isometric(&x1, &y1, z1);
	printf("After iso: (x:%d y:%d)\n", x, y);
	printf("After iso: (x1:%d y1:%d)\n", x1, y1);
	x += data->img.width / 3;
	y += data->img.height / 3;
	x1 += data->img.width / 3;
	y1 += data->img.height / 3;
	max = find_max(abs(x_step), abs(y_step));
	x_step /= max;
	y_step /= max;
	while ((x - x1) || (y - y1))
	{
		put_pixel(&data->img, x, y, WHITE);
		x += x_step;
		y += y_step;
	}
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
			if (x < data->width -1)
				draw_line(data, x, y, x + 1, y);
			if (y < data->height -1)
				draw_line(data, x, y, x, y + 1);
			x++;
		}
		y++;
	}
}

t_fdf	new_program(int w, int h, char *str)
{
	t_fdf fdf;

	fdf.mlx_ptr = mlx_init();
	fdf.width = w;
	fdf.height = h;
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, w * SIZE, h * SIZE, str);
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
	*data = new_program(data->width, data->height, "fdf");
	if (!data->mlx_ptr || !data->win_ptr)
		return (1);
	data->img = new_img(*data);
	//draw_line(&(data->img), 10, 10, 110, 110);
	draw_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	mlx_hook(data->win_ptr, 17, 0, exit_window, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
