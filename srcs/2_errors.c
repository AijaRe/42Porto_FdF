/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_errors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:34:31 by arepsa            #+#    #+#             */
/*   Updated: 2023/07/31 15:35:06 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	ft_freematrix(t_fdf *data, int i)
{
	free_tab(data->map);
	while (i >= 0)
	{
		if (data->z_matrix[i])
			free(data->z_matrix[i]);
		i--;
	}
	free(data->z_matrix);
	free(data);
}

void	ft_map_error(t_fdf *data, int i, char *message)
{
	ft_freematrix(data, i);
	ft_error(message);
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
