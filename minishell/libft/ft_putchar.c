/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:33:20 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/02/01 01:08:43 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c, int *count)
{
	ssize_t	result;

	result = write(1, &c, 1);
	if (result == -1)
	{
		(*count) = -1;
		return ;
	}
	(*count)++;
}
