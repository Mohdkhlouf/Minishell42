/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:10:51 by mkhlouf           #+#    #+#             */
/*   Updated: 2024/11/13 16:37:08 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*joined_str;
	unsigned int	joined_str_len;
	unsigned int	i;
	unsigned int	j;

	joined_str_len = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	joined_str = malloc((joined_str_len + 1) * sizeof(char));
	if (!joined_str)
		return (NULL);
	while (s1[i])
		joined_str[i++] = s1[j++];
	j = 0;
	while (s2[j])
		joined_str[i++] = s2[j++];
	joined_str[i] = '\0';
	return (joined_str);
}
