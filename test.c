#include "mlx/mlx.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

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

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dest;

	if (x >= 00 && y >= 0 && x < img->width && y < img->height)
	{
	dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dest = color;
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

	img.win = new_win;
	img.img = mlx_new_image(new_win.mlx, new_win.width/1.5, new_win.height/1.5);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	img.width = new_win.width/1.5;
	img.height = new_win.height/1.5;
	return (img);
}
int	exit_window(t_win *win)
{
	if (win)
		mlx_destroy_window(win->mlx, win->mlx_win);
		exit (EXIT_SUCCESS);
}

int	main(void)
{
	t_win	new_win;
	t_img	img;

	new_win = new_program(500, 300, "My Window");
	if (!new_win.mlx || !new_win.mlx_win)
		return (1);
	img = new_img(new_win);
	my_mlx_pixel_put(&img, new_win.width/2, new_win.height/2, 0x00FFEA00);
	mlx_put_image_to_window(new_win.mlx, new_win.mlx_win, img.img, 0, 0);
	mlx_hook(new_win.mlx_win, 17, 0, exit_window, &new_win);
	mlx_loop(new_win.mlx);
	return (0);
}
