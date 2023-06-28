#include "mlx/mlx.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <math.h>
# define ESC 65307

typedef struct s_win {
	void	*mlx;
	void	*mlx_win;
	int		width;
	int		height;
}				t_win;

typedef struct	s_img {
	t_win	win;
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_square {
	unsigned short int	x;
	unsigned short int	y;
	unsigned short int	size;
	int					color;
}		t_square;


void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && y >= 0 && x < img->width && y < img->height)
	{
		pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int*)pixel = color;
	}
}

void	draw_square(t_square square, t_img img)
{
	unsigned short int	i;
	unsigned short int	j;

	i = 0;
	while (i < square.size && i + square.y < img.height)
	{
		j = 0;
		while (j < square.size && j + square.x < img.width)
		{
			put_pixel(&img, j + square.x, i + square.y, square.color);
			j++;
		}
		i++;
	}
}

void	draw_full_line(t_img *img, int x, int y, int color)
{
	char	*dest;

	while (x >= 0 && y >= 0 && x < img->width && y < img->height)
	{
		dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int*)dest = color;
		x++;
	}
}

void draw_line(t_img *img, int x1, int y1, int x2, int y2, int color)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx, sy, err;

	if (x1 < x2)
		sx = 1;
	else
		sx = -1;

	if (y1 < y2)
		sy = 1;
	else
		sy = -1;

	err = dx - dy;

	while (x1 != x2 || y1 != y2)
	{
		put_pixel(img, x1, y1, color);
		int err2 = 2 * err;

		if (err2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}

		if (err2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

t_win	new_program(int w, int h, char *str)
{
	t_win win;

	win.mlx = mlx_init();
	win.width = w;
	win.height = h;
	win.mlx_win = mlx_new_window(win.mlx, w, h, str);
	return (win);
}

t_img	new_img(t_win new_win)
{
	t_img	img;

	//img.win = new_win;
	img.img = mlx_new_image(new_win.mlx, new_win.width, new_win.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	img.width = new_win.width;
	img.height = new_win.height;
	return (img);
}
int	exit_window(t_win *win)
{
	if (win)
		mlx_destroy_window(win->mlx, win->mlx_win);
		mlx_destroy_display(win->mlx);
		free(win->mlx);
		exit (EXIT_SUCCESS);
		//return (0);
}

int	handle_key_event(int key_pressed, void	*param)
{
	t_img	*img;

	img = (t_img *)param;
	if (key_pressed == ESC || !img)
		exit_window(&img->win);
	else
        return (-1);
    //mlx_put_image_to_window(img->win.mlx, img->win.mlx, img->img, 0, 0);
    return (0);
}

int	main(void)
{
	t_win	new_win;
	t_img	img;

	new_win = new_program(500, 300, "My Window");
	if (!new_win.mlx || !new_win.mlx_win)
		return (1);
	img = new_img(new_win);
	//put_pixel(&img, new_win.width/2, new_win.height/2, 0x00FFEA00);
	draw_square((t_square){100, 100, 50, 0x00FFEA00}, img);
	draw_full_line(&img, 0, 50, 0x00FFEA00);
	draw_line(&img, 10, 10, 100, 80, 0x00FF00);
	mlx_put_image_to_window(new_win.mlx, new_win.mlx_win, img.img, 0, 0);
	mlx_hook(new_win.mlx_win, 17, 0, exit_window, &new_win);
	mlx_key_hook(new_win.mlx_win, &handle_key_event, &img);
	mlx_loop(new_win.mlx);
	return (0);
}
