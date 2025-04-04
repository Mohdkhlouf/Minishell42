/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:57:01 by akumari           #+#    #+#             */
/*   Updated: 2024/11/14 10:46:25 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	if (len == 0)
		return (NULL);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (j < ft_strlen(little) && ((i + j) < len))
		{
			if (big[i + j] != little[j])
				break ;
			j++;
		}
		if (j == ft_strlen(little))
			return ((char *)&big[i]);
		if ((i + j) == len)
			return (NULL);
		i++;
	}
	return (NULL);
}
