/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:37:23 by arepsa            #+#    #+#             */
/*   Updated: 2023/07/31 15:37:33 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <errno.h>
# include <math.h>

# define ESC 65307
# define WIDTH 1920
# define HEIGHT 1200
# define WHITE 0x00FFFFFF

typedef struct s_bresenham
{
	int	x0;
	int	y0;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}		t_bresenham;

typedef struct s_dot{
	int	x;
	int	y;
	int	z;
	int	color;
}		t_dot;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_fdf
{
	int		width;
	int		height;
	char	**map;
	t_dot	**z_matrix;
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}				t_fdf;

/*program initialization, structure and mlx related functions*/
int		main(int argc, char **argv);

/*error handling*/
void	handle_input_errors(int argc, char *file);
void	ft_map_error(t_fdf *data, int i, char *message);
void	ft_freematrix(t_fdf *data, int i);
void	free_tab(char **tab);
void	ft_error(char *msg);

/*map reading*/
void	get_map(t_fdf *data, char *file_name);
void	read_file(t_fdf *data);

/*drawing, map and pixel transformation*/
void	draw_map(t_fdf *data);
void	draw_line(t_fdf *data, t_dot *a, t_dot *b);
void	transform_map(t_fdf *data, t_dot *a, t_dot *b);
void	put_pixel(t_img *img, int x, int y, int color);
int		get_color(t_dot *a, t_dot *z);

#endif
