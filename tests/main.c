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
void	print_map(t_fdf *data)
{
	for(int i = 0; i < data->height; i++)
	{
		for (int j = 0; j < data->width; j++)
		{
			printf("%d ", data->map[i][j]);
		}
		printf("\n");
	}
}

void	ft_error(char *msg)
{
	ft_printf("Error : %s\n", msg);
	exit(EXIT_FAILURE);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	get_width(char *filename, int check)
{
	int		fd;
	char	**map;
	int		count;
	int		j;
	char	*line;

	if (check == 1)
	{
		fd = open(filename, O_RDONLY);
		line = get_next_line(fd);
		map = ft_split(line, ' ');
	}
	else
		map = ft_split(filename, ' ');
	count = 0;
	while (map[count])
		count++;
	j = 0;
	while (map[j])
	{
		free(map[j]);
		j++;
	}
	free(map);
	if (check == 1)
		free(line);
	printf("width %d\n", count);
	return (count);
}

int	get_height(char *filename)
{
	int		count;
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		count++;
	}
	printf("Height: %d\n", count);
	return (count);
}

void	fill_map(int *num_map, int *color_map, char *line)
{
	char	**char_map;
	int		i;
	int		j;
	int		k;

	char_map = ft_split(line, ' ');
	i = 0;
	while (char_map[i])
	{
		num_map[i] = ft_atoi(char_map[i]);
		//printf("*%d ", num_map[i]);
		k = 0;
		while (char_map[i][k] != ',' && char_map[i][k])
			k++;
		if (char_map[i][k++] == ',')
		{
			color_map[i] = ft_atoi_hex(ft_strchr(char_map[i], ',') + 3);
		}
		else
			color_map[i] = 0;
		i++;
	}
	j = 0;
	while (char_map[j])
		free(char_map[j++]);
	free(char_map);
} 

int	check_read(char *filename)
{
	int		bytes;
	int		fd;
	char	*buf;

	fd = open(filename, O_RDONLY);
	buf = malloc(sizeof(char) * 2);
	bytes = read(fd, buf, 2);
	if (bytes <= 0)
		return (1);
	free(buf);
	return (0);
}

void	get_map(t_fdf *ptr, char *filename)
{
	int		i;
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0 || check_read(filename))
		ft_error("Couldn't open or empty file.");
	i = 0;
	ptr->width = get_width(filename, 1);
	ptr->height = get_height(filename);
	ptr->map = (int **) malloc(sizeof(int *) * (ptr->height));
	ptr->color_map = (int **) malloc(sizeof(int *) * (ptr->height));
	while (i < ptr->height)
	{
		ptr->map[i] = (int *) malloc(sizeof(int) * ptr->width);
		ptr->color_map[i] = (int *) malloc(sizeof(int) * ptr->width);
		line = get_next_line(fd);
		if (ptr->width != get_width(line, 0))
			ft_error("Invalid file.");
		fill_map(ptr->map[i], ptr->color_map[i], line);
		free(line);
		i++;
	}
	print_map(ptr);
	//ptr->map[i] = NULL;
	// for(i = 0; i<ptr->width; i++)
	// {
	// 	free(ptr->map[i]);
	// }
	for(i = 0; i<ptr->width; i++)
	{
		free(ptr->color_map[i]);
	}
	//free(ptr->map);
	free(ptr->color_map);
}

// void	put_pixel(t_img *img, int x, int y, int color)
// {
// 	char	*pixel;

// 	if (x >= 0 && y >= 0 && x < img->width && y < img->height)
// 	{
// 		pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
// 		*(unsigned int *)pixel = color;
// 	}
// }

// static void	bresenham_define(t_bresenham *param, t_dot *a, t_dot *b)
// {
// 	param->dx = abs(b->x - a->x);
// 	param->dy = -1 * abs(b->y - a->y);
// 	if (a->x <= b->x)
// 		param->sx = 1;
// 	else
// 		param->sx = -1;
// 	if (a->y <= b->y)
// 		param->sy = 1;
// 	else
// 		param->sy = -1;
// 	param->err = param->dx + param->dy;
// 	param->x0 = a->x;
// 	param->y0 = a->y;
// }

// void	draw_line(t_fdf *data, t_dot *a, t_dot *b)
// {
// 	t_bresenham	param;

// 	//transform_map(data, a, b);
// 	bresenham_define(&param, a, b);
// 	while (1)
// 	{
// 		if (param.x0 < WIDTH && param.x0 > 0
// 			&& param.y0 < HEIGHT && param.y0 > 0)
// 			put_pixel(&data->img, param.x0, param.y0, WHITE);
// 		if (param.x0 == b->x && param.y0 == b->y)
// 			break ;
// 		if (2 * param.err >= param.dy && param.x0 != b->x)
// 		{
// 			param.err += param.dy;
// 			param.x0 += param.sx;
// 		}
// 		if (2 * param.err <= param.dx && param.y0 != b->y)
// 		{
// 			param.err += param.dx;
// 			param.y0 += param.sy;
// 		}
// 	}
// }
void	set_coordinates(t_fdf *data, int x, int y, int check)
{
	t_dot a;
	t_dot b;
	print_map(data);
	a.x = x;
	a.y = y;
	printf("x:%d y:%d\n", a.x, a.y);
	a.z = data->map[x][y];

	if (check == 0)
	{
		b.x = x + 1;
		b.y = y;
		b.z = data->map[x + 1][y];
	}
	if (check == 1)
	{
		b.x = x;
		b.y = y + 1;
		b.z = data->map[x][y + 1];
	}

	// if (check == 0)
	// {
	// 	data->x = x;
	// 	data->x1 = x + 1;
	// 	data->y = y;
	// 	data->y1 = y;
	// }
	// if (check == 1)
	// {
	// 	data->x = x;
	// 	data->x1 = x;
	// 	data->y = y;
	// 	data->y1 = y + 1;
	// }
	//draw_line(data, &a, &b);
} 

void	draw_map(t_fdf *data)
{
	int	x;
	int	y;
	print_map(data);
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			//data->color = data->color_map[y][x];
			if (x < (data->width - 1))
			{
				printf("horizontal x: %d y: %d\n", x, y);
				set_coordinates(data, x, y, 0);
			}
			if (y < (data->height - 1))
			{
				printf("vertical x: %d y: %d\n", x, y);
				set_coordinates(data, x, y, 1);
			}
			x++;
		}
		y++;
	}
	// for(i = 0; i<data->width; i++)
	// {
	// 	free(data->color_map[i]);
	// }
	// free(data->color_map);
} 

void	handle_input_errors(int argc, char *file)
{
	int	fd;

	if (argc != 2)
	{
		ft_error("Invalid input\nValid input:\n./fdf <filename.fdf>");
	}
	fd = open(file, O_RDONLY, 0);
	if (fd == -1)
	{
		ft_error("Failed to open the file");
	}
	else
		close(fd);
}

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

void	new_program(t_fdf *data, char *str)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, str);
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
void	init_data(t_fdf *data)
{
	data->width = 0;
	data->height = 0;
	//int		**map;
	//int 	**color_map;
	data->color = 0;
	data->x = 0;
	data->x1 = 0;
	data->y = 0;
	data->y1 = 0;
	//data->mlx_ptr = NULL;
	//data->win_ptr = NULL;
	//t_img	img;
}

int	main(int argc, char **argv)
{
	t_fdf	*data;

	handle_input_errors(argc, argv[1]);
	data = (t_fdf *)malloc(sizeof(t_fdf));
	init_data(data);
	get_map(data, argv[1]);
	print_map(data);
	//read_file(data);
	new_program(data, "fdf");
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
