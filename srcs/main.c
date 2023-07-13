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
	ft_printf("Error : %s\n", msg);
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
		//free(data->z_matrix[i]);
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

	img.img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	if (img.img == NULL)
		ft_error("Failed to create image.");
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length,
								&img.endian);
	img.width = WIDTH;
	img.height = HEIGHT;
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
	int	x_tmp;
	int	y_tmp;

	x_tmp = *x;
	y_tmp = *y;
	*x = (x_tmp - y_tmp) * cos(0.523599);
	*y = (x_tmp + y_tmp) * sin(0.523599) - z;

}

void	scale_map(t_fdf *data, int *x1, int *y1, int *x2, int *y2)
{
	float map_diagonal;
	float factor;
	
	map_diagonal = sqrt(data->width*data->width + data->height*data->height);
	factor = 0.9 * HEIGHT / map_diagonal;
	*x1 *= round(factor);
	*y1 *= round(factor);
	*x2 *= round(factor);
	*y2 *= round(factor);
}

void	center_map(int *x1, int *y1, int *x2, int *y2)
{
    int x_offset = WIDTH * 2 / 5;;
    int y_offset = HEIGHT * 1 / 5;

    *x1 += x_offset;
    *y1 += y_offset;
    *x2 += x_offset;
    *y2 += y_offset;
}

static void	bresenham_define(t_bresenham *param, int *x1, int *y1, int *x2, int *y2)
{
	param->dx = abs(*x2 - *x1);
	param->dy = -1 * abs(*y2 - *y1);
	if (*x1 <= *x2)
		param->sx = 1;
	else
		param->sx = -1;
	if (*y1 <= *y2)
		param->sy = 1;
	else
		param->sy = -1;
	param->err = param->dx + param->dy;
	param->x0 = *x1;
	param->y0 = *y1;
}
void draw_line(t_fdf *data, int x1, int y1, int x2, int y2)
{
	int z1;
	int z2;
	t_bresenham	*param;

	z1 = data->z_matrix[y1][x1];
	z2 = data->z_matrix[y2][x2];
	scale_map(data, &x1, &y1, &x2, &y2);
	isometric(&x1, &y1, z1);
	isometric(&x2, &y2, z2); 
	center_map(&x1, &y1, &x2, &y2);
	param = (t_bresenham *)malloc(sizeof(t_bresenham));
	bresenham_define(param, &x1, &y1, &x2, &y2);
	while (1)
	{
		if (param->x0 < WIDTH && param->x0 > 0 && param->y0 < HEIGHT && param->y0 >0)
			put_pixel(&data->img, param->x0, param->y0, WHITE);
		if (param->x0 == x2 && param->y0 == y2)
			break ;
		param->err2 = 2 * param->err;
		if (param->err2 >= param->dy && param->x0 != x2)
		{
			param->err += param->dy;
			param->x0 += param->sx;
		}
		if (param->err2 <= param->dx && param->y0 != y2)
		{
			param->err += param->dx;
			param->y0 += param->sy;
		}
	}
	free(param);
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
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, WIDTH, HEIGHT, str);
	return (fdf);
}
int	exit_window(t_fdf *win)
{
	if (win)
	{
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
		free(win->mlx_ptr);
		//free(win);
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
