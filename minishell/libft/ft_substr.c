/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhlouf <mkhlouf@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:59:48 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/03/27 12:44:20 by mkhlouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*sub;
// 	size_t	slen;
// 	size_t	i;

// 	slen = ft_strlen(s);
// 	if (!s)
// 		return (NULL);
// 	if (start >= slen)
// 		return (ft_strdup(""));
// 	if (len > slen - start)
// 		len = slen - start;
// 	sub = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!sub)
// 		exit(EXIT_FAILURE);;
// 	i = 0;
// 	while (s[start + i] && i < len)
// 	{
// 		sub[i] = s[start + i];
// 		i++;
// 	}
// 	sub[i] = '\0';
// 	return (sub);
// }
char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char *substr;
	size_t i;

	i = 0;
	if (!s)
		return (NULL);
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[len] = '\0';
	return (substr);
}