/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:19:41 by arepsa            #+#    #+#             */
/*   Updated: 2023/04/14 14:19:45 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*count the length of the integer*/
/*how many times it divides by 10*/
/*negatives get extra space for '-'*/
static	int	ft_length(int n)
{
	int	length;

	length = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		length++;
	while (n)
	{
		n = n / 10;
		length++;
	}
	return (length);
}

static char	*ft_max_neg(void)
{
	char	*res;

	res = malloc(sizeof(char) * 12);
	ft_strlcpy(res, "-2147483648", 12);
	return (res);
}

/*convert integer to character*/
/*0 has a special condition because can't divide by 0*/
/*cap the last position with NUl before altering length variable*/
/*start form last position and fill with the remainder as character*/
/*to get the next number, divide by 10 and back up one position*/
char	*ft_itoa(int n)
{
	char	*res;
	int		len;

	if (n == -2147483648)
		return (ft_max_neg());
	len = ft_length(n);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == 0)
		return (0);
	if (n == 0)
		res[0] = '0';
	if (n < 0)
	{
		n *= -1;
		res[0] = '-';
	}
	res[len] = '\0';
	while (n != 0)
	{
		res[len - 1] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	return (res);
}
