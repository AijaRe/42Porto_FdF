/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:04:26 by arepsa            #+#    #+#             */
/*   Updated: 2023/05/16 10:04:30 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_ptr(unsigned long long ptr, char *base, int *count)
{
	if (ptr == 0)
		ft_putstr_pf("(nil)", count);
	else
	{
		ft_putstr_pf("0x", count);
		ft_putnbr_ptr(ptr, base, count);
	}
}

void	ft_putnbr_ptr(unsigned long long ptr, char *base, int *count)
{
	if (ptr < 16)
		ft_putchar_pf(base[ptr], count);
	if (ptr >= 16)
	{
		ft_putnbr_ptr(ptr / 16, base, count);
		ft_putnbr_ptr(ptr % 16, base, count);
	}
}
