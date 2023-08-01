
#include "mlx/mlx.h"
#include <errno.h>
#include <stdlib.h>
# define ESC 65307   // key escape
# define ENTER 65293 // key "enter"
# define FOLLOW 102 // key "f"
# define COLOR 99  // key "c"
# define UP 65362   // key "arrow up"
# define DOWN 65364 // key "arrow down"
# define PENGUIN 112 // key "p"
# define RAND_COLOR 114 // key "r"

typedef struct s_prog
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		height;
	int		width;
}	t_prog;

typedef struct s_img
{
	t_prog	prog;
	void	*img_ptr;
	char	*addr;

	int		height;
	int		width;
	int		bpp; //bit per pixel
	int		line_len; //nb of bytes
	int		endian;
}	t_img;
/* x and y represent the top left corner of the square, 
the size represents the width and height of the square. */
typedef struct	s_square{
	unsigned short int	x;
	unsigned short int	y;
	unsigned short int	size;
	int					color;
}	t_square;

int size = 10;
int follow = 0;
int	color;

t_prog	new_program(int w, int h, char *str)
{
	void	*mlx_ptr;
	t_prog	prog;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		exit (EXIT_FAILURE);
	prog = (t_prog){mlx_ptr, mlx_new_window(mlx_ptr, w, h, str), w, h};
	return (prog);
}

t_img	new_image(int w, int h, t_prog prog)
{
	t_img	img;
	img.prog = prog;
	img.img_ptr = mlx_new_image(prog.mlx_ptr, w, h);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.line_len, &img.endian);
	img.width = w;
	img.height = h;
	return (img);
}

void	put_pixel(t_img img, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && y >= 0 && x < img.width && y < img.height)
	{
		pixel = img.addr + (y *img.line_len + x * (img.bpp/8));
		*(unsigned int *)pixel = color;
	}
}

int		exit_program(t_prog *prog)
{
	if (prog)
		mlx_destroy_window(prog->mlx_ptr, prog->win_ptr);
	exit (EXIT_SUCCESS);
}

void	draw_square(t_square square, t_img img)
{
	unsigned short int	x;
	unsigned short int	y;

	y = 0;
	while (y < square.size && y + square.y <img.height)
	{
		x = 0;
		while (x < square.size && x + square.x < img.width)
		{
			put_pixel(img, square.x + x, square.y + y, square.color);
			x++;
		}
		y++;
	}
}
t_square	create_square(int x, int y, int size, int color)
{
	t_square sq;

	sq.x = x;
	sq.y = y;
	sq.size = size;
	sq.color = color;
	return (sq);
}

int get_color()
{
        return (rand() % 2147483647);
}

int     read_keys(int key_pressed, void *param)
{
        t_img *img;

        img = (t_img *)param;
        if (key_pressed == ESC || !img)
                exit_program(&img->prog);
        else if (key_pressed == ENTER)
                draw_square((t_square){0, 0, img->width, 0xFFFFFF}, *img);
        else if (key_pressed == FOLLOW)
                follow = !follow;
        else if (key_pressed == COLOR)
                color = get_color();
		else if (key_pressed == UP)
				size += 2;
		else if (key_pressed == DOWN)
				size -= 2;
        else
                return (-1);
        mlx_put_image_to_window(img->prog.mlx_ptr, img->prog.win_ptr, img->img_ptr, 0, 0);
        return (0);
}

int read_mouse(int button, int mouse_x, int mouse_y, void *param)
{
	int 		x;
	int 		y;
	t_img 		*img;
	t_square	s;

	img = (t_img *) param;
	if (!img)
		return (-1);
	if (mouse_x < 0 || mouse_y < 0 || mouse_x > img->width || mouse_y > img->height)
		return (2);
	x = ((mouse_x % img->width) / size) * size;
	y = ((mouse_y % img->height) / size) * size;
	s = (t_square){x, y, size, color};
	draw_square(s, *img);
	mlx_put_image_to_window(img->prog.mlx_ptr, img->prog.win_ptr, img->img_ptr, 0, 0);
	(void)button;
	return (0);
}

int	main(void)
{
	t_prog	prog;
	t_img	image;
	t_square	square;

	prog = new_program(300, 300, "test_mlx");
	if (!prog.mlx_ptr || !prog.win_ptr)
		return (1);
	image = new_image(300, 300, prog);
	square = create_square(0, 0, 300, 0x00FFCC00);
	put_pixel(image, 150, 150, 0x00FFFF00);
	draw_square(square, image);
	mlx_put_image_to_window(image.prog.mlx_ptr, image.prog.win_ptr, image.img_ptr, 0, 0);
	mlx_key_hook (prog.win_ptr, read_keys, &image);
	mlx_mouse_hook(prog.win_ptr, read_mouse, &image);
	mlx_hook(prog.win_ptr, 17, 0, exit_program, &prog);
	mlx_loop(prog.mlx_ptr);
	return (0);
}