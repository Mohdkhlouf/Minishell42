/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:01:09 by akumari           #+#    #+#             */
/*   Updated: 2024/11/15 09:16:11 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*int_to_str(int n, char *new_str, int i, int nbr)
{
	if (nbr == -2147483648)
	{
		ft_strlcpy(new_str, "-2147483648", 12);
		return (new_str);
	}
	if (nbr < 0)
	{
		nbr = -n;
		new_str[0] = '-';
	}
	while (nbr != 0)
	{
		new_str[i] = nbr % 10 + '0';
		nbr = nbr / 10;
		i--;
	}
	return (new_str);
}

char	*ft_itoa(int n)
{
	char	*new_str;
	int		i;
	int		nbr;
	int		len;

	if (n == 0)
	{
		new_str = (char *)malloc(2);
		if (!new_str)
			return (NULL);
		new_str[0] = '0';
		new_str[1] = '\0';
		return (new_str);
	}
	i = 0;
	nbr = n;
	len = int_len(n);
	new_str = (char *)malloc(len + 1);
	if (!new_str)
		return (NULL);
	i = len - 1;
	new_str[len] = '\0';
	new_str = int_to_str(n, new_str, i, nbr);
	return (new_str);
}
