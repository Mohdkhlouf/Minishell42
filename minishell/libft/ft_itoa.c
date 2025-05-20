/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:47:11 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/05/19 11:55:42 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n);
static int	count_int(long n);
static char	*convertt(long n, char *str, int counter);

static char	*convertt(long n, char *str, int counter)
{
	int	i;

	i = counter - 1;
	if (n == 0)
		str[i] = 0 + 48;
	else if (n < 0)
	{
		n = n * -1;
		str[0] = '-';
	}
	while (n > 0)
	{
		str[i] = n % 10 + 48;
		n = n / 10;
		i--;
	}
	str[counter] = '\0';
	return (str);
}

static int	count_int(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nn;

	nn = n;
	str = malloc((count_int(nn) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	convertt(nn, str, count_int(nn));
	return (str);
}
