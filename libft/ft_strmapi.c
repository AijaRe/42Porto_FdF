/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:28:18 by arepsa            #+#    #+#             */
/*   Updated: 2023/04/19 18:09:19 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Applies the function ’f’ to each character of the
string ’s’, and passing its index as first argument
to create a new string with malloc resulting
from successive applications of ’f’.*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*res;

	res = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!res)
		return (NULL);
	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			res[i] = (*f)(i, s[i]);
			i++;
		}
	}
	res[i] = '\0';
	return (res);
}
