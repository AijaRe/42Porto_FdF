/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:13:39 by arepsa            #+#    #+#             */
/*   Updated: 2023/04/14 12:13:43 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*concatenate s2 to s1*/
/*return a new string allocated with malloc*/
/*copy s1 into final string to return*/
/*concatinate s2 to the final string*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	int		total_len;

	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = (char *)malloc(sizeof(char) * total_len);
	if (!joined)
		return (NULL);
	ft_strlcpy(joined, s1, total_len);
	ft_strlcat(joined, s2, total_len);
	return (joined);
}
