/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:51:08 by arepsa            #+#    #+#             */
/*   Updated: 2023/04/12 18:52:11 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*appends the NUL-terminated string src to the end of dst.
It will append at most (size - strlen(dst) - 1) bytes*/
/*NUL-terminate the result*/
/*return total lenght of the string tried to create..*/
/*..to detect truncation*/
/*if size < d_len (doesn't have space to cat)..*/
/*..the d_len is considered to be size*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;
	size_t	i;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	i = 0;
	if (size <= d_len)
		return (size + s_len);
	while (src[i] != '\0' && i < (size - d_len - 1))
	{
		dst[d_len + i] = src[i];
		i++;
	}
	dst[d_len + i] = '\0';
	return (d_len + s_len);
}
