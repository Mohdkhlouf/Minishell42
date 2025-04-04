/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:47:59 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/02/01 01:08:43 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	after_specifier(unsigned char c, va_list args, int *count)
{
	if (c == 'd')
		ft_putnbr((va_arg(args, int)), count);
	else if (c == 'c')
		ft_putchar(va_arg(args, int), count);
	else if (c == 's')
		ft_putstr(va_arg(args, char *), count);
	else if (c == 'i')
		ft_putnbr((va_arg(args, int)), count);
	else if (c == 'p')
		ft_putptr((va_arg(args, void *)), count);
	else if (c == '%')
		ft_putchar('%', count);
	else if (c == 'u')
		ft_putnbr_unsigned((va_arg(args, unsigned int)), count);
	else if (c == 'x')
		ft_putnbr_hex((va_arg(args, unsigned int)), count, 'x');
	else if (c == 'X')
		ft_putnbr_hex((va_arg(args, unsigned int)), count, 'X');
	else
		(*count) = -1;
}

int	ft_printf(const char *num, ...)
{
	va_list			args;
	unsigned int	i;
	int				count;

	count = 0;
	i = 0;
	va_start(args, num);
	while (num[i] != '\0' && count >= 0)
	{
		if (num[i] == '%')
		{
			after_specifier(num[i + 1], args, &count);
			i = i + 2;
		}
		else
		{
			ft_putchar(num[i], &count);
			i++;
		}
	}
	va_end(args);
	return (count);
}
