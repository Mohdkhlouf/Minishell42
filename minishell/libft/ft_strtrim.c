/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:09:07 by mkhlouf           #+#    #+#             */
/*   Updated: 2024/11/13 16:38:08 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		else
			i++;
	}
	return (0);
}

static int	left_count(char const *s1, char const *set)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (check(s1[i], set) == 1)
	{
		i++;
		counter++;
	}
	return (counter);
}

static int	right_count(char const *s1, char const *set)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	i = ft_strlen(s1);
	while (check(s1[i - 1], set) == 1)
	{
		counter++;
		i--;
	}
	return (counter);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*newstr;
	int		start;
	int		end;

	start = 0;
	end = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	start = left_count(s1, set);
	end = right_count(s1, set);
	newstr = ft_substr(s1, start, (ft_strlen(s1) - end - start));
	return (newstr);
}
