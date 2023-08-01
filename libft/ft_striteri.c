/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:07:14 by arepsa            #+#    #+#             */
/*   Updated: 2023/04/19 13:08:18 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*Apply the function ’f’ on each char of the str passed as argument,*/
/*passing its index as first argument.*/
/*Each character is passed by address to ’f’ to be modified if necessary.*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			(*f)(i, &s[i]);
			i++;
		}
	}
}
