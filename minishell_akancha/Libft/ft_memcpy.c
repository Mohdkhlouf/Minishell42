/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:56:05 by akumari           #+#    #+#             */
/*   Updated: 2024/11/14 13:01:12 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned const char	*s;
	unsigned char		*d;

	if (dest == NULL && src == NULL)
		return (NULL);
	s = (unsigned const char *)src;
	d = (unsigned char *)dest;
	if (d == s || n == 0)
		return (dest);
	while (n > 0)
	{
		*(d++) = *(s++);
		n--;
	}
	return (dest);
}
