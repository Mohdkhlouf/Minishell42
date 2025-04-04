/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AbhishekKumar <AbhishekKumar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:34:46 by akumari           #+#    #+#             */
/*   Updated: 2025/03/31 15:12:53 by AbhishekKum      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strndup(const char *s, size_t n)
{
	char *dup;
	size_t i;

	dup = (char *)malloc(n + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static const char *ft_find_next_word(const char *s, char c, int *len)
{
	const char *start;

	while (*s && *s == c)
		s++;
	start = s;
	*len = 0;
	while (*s && *s != c)
	{
		(*len)++;
		s++;
	}
	return (start);
}

static void ft_free_array(char **arr, int i)
{
	int j;

	j = 0;
	while (j < i)
	{
		free(arr[j]);
		j++;
	}
	free(arr);
}

static char **ft_split_words(const char *s, char c, char **arr)
{
	int i;
	const char *start;
	int len;

	i = 0;
	while (*s)
	{
		start = ft_find_next_word(s, c, &len);
		if (len > 0)
		{
			arr[i] = ft_strndup(start, len);
			if (!arr[i])
			{
				ft_free_array(arr, i);
				return (NULL);
			}
			i++;
		}
		s = start + len;
	}
	arr[i] = NULL;
	return (arr);
}

char **ft_split(char const *s, char c)
{
	char **arr;
	size_t count;
	int in_word;
	char const *str;

	str = s;
	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			count++;
			in_word = 1;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	if (!ft_split_words(str, c, arr))
		return (NULL);
	return (arr);
}
