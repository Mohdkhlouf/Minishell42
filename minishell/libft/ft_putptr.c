/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:34:17 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/02/01 01:08:43 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putptr(void *n, int *count)
{
	uint64_t	ptr;

	ptr = (uint64_t)n;
	if (!n)
		ft_putstr("(nil)", count);
	else
	{
		ft_putchar('0', count);
		ft_putchar('x', count);
		ft_putnbr_hex(ptr, count, 'x');
	}
}
