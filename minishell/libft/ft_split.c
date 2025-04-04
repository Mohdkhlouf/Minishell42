/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:59:49 by mkhlouf           #+#    #+#             */
/*   Updated: 2025/04/04 12:09:57 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free(char **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static int	word_count(const char *s, char c)
{
	size_t	i;
	int		wcounter;
	int		inword;

	i = 0;
	inword = 0;
	wcounter = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != c && inword == 0)
		{
			inword = 1;
			wcounter++;
		}
		else if (s[i] == c)
			inword = 0;
		i++;
	}
	return (wcounter);
}

static char	*fill_word(const char *s, int word_start, int i)
{
	char	*word;
	int		j;

	j = 0;
	word = malloc((i - word_start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (word_start < i)
	{
		word[j] = s[word_start];
		word_start++;
		j++;
	}
	word[j] = '\0';
	return (word);
}

static char	**loop(char **arr, char c, char *s, int word_start)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if ((s[i] != c) && word_start < 0)
			word_start = i;
		if ((s[i] == c || s[i + 1] == '\0') && word_start >= 0)
		{
			if (s[i + 1] == '\0' && s[i] != c)
				arr[j] = fill_word(s, word_start, i + 1);
			else
				arr[j] = fill_word(s, word_start, i);
			if (!(arr[j]))
				return (ft_free(arr, j));
			word_start = -1;
			j++;
		}
		i++;
	}
	arr[j] = NULL;
	return (arr);
}

char	**ft_split(char *s, char c)
{
	char	**arr;
	int		word_start;

	word_start = -1;
	if (!s)
	{
		arr = malloc(sizeof (char*) * 1);
		arr[0] = NULL;
	}
	else
	{
		arr = malloc((word_count(s, c) + 1) * sizeof(char *));
		if (!arr)
			return (NULL);
		arr = loop(arr, c, (char *)s, word_start);
	}
	return (arr);
}
