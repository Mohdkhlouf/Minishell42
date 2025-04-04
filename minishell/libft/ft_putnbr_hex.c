/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:53:14 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/02/01 01:08:43 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_letters(uint64_t n, int *count, unsigned char x)
{
	if (n == 10)
		ft_putchar('a' - x, count);
	else if (n == 11)
		ft_putchar('b' - x, count);
	else if (n == 12)
		ft_putchar('c' - x, count);
	else if (n == 13)
		ft_putchar('d' - x, count);
	else if (n == 14)
		ft_putchar('e' - x, count);
	else if (n == 15)
		ft_putchar('f' - x, count);
}

void	ft_putnbr_hex(uint64_t n, int *count, unsigned char c)
{
	unsigned char	x;

	x = 0;
	if (c == 'X')
		x = 32;
	if (n > 15)
	{
		ft_putnbr_hex(n / 16, count, c);
		ft_putnbr_hex(n % 16, count, c);
	}
	else
	{
		if (n < 10)
			ft_putnbr(n, count);
		else
			print_letters(n, count, x);
	}
}
