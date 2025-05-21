/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:15:39 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/05/21 12:57:51 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// changed for exit
static int	ft_skip_ws_and_sign(char *str, int *sign)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

long	ft_atoi(char *str)
{
	int		sign;
	int		i;
	long	num;

	i = 0;
	sign = 1;
	num = 0;
	i = ft_skip_ws_and_sign(str, &sign);
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (num > (LONG_MAX - (str[i] - '0')) / 10)
		{
			if (sign == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * sign);
}
