#ifndef FDF_H
# define FDF_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <math.h>

# define ESC 65307
# define UP 65362
# define DOWN 65364
# define WIDTH 800
# define HEIGHT 500
# define WHITE 0x00FFFFFF


typedef struct	s_img {
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
	int		**z_matrix;
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
} 				t_fdf;

int	main(int argc, char **argv);

#endif
