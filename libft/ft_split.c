/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 00:10:01 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 13:07:14 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*take_word(char const *s, int start, int end)
{
	char	*word;
	int		i;

	word = (char *)malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static void	free_all(char **arr, int words_count)
{
	int	i;

	i = 0;
	while (i < words_count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	fill_word(char **arr, const char *s, char c, int count)
{
	int	i;
	int	start;

	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			arr[count] = take_word(s, start, i);
			if (!arr[count])
				return (-1);
			count++;
		}
	}
	arr[count] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		words_count;

	if (!s)
		return (NULL);
	words_count = count_words(s, c);
	arr = (char **)malloc((words_count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	if (fill_word(arr, s, c, 0) == -1)
	{
		free_all(arr, words_count);
		return (NULL);
	}
	return (arr);
}

// #include <stdio.h>
// int main()
// {
// 	char **result;
// 	int i;

// 	result = ft_split("Hello,,World,,42", ',');
// 	if (result)
// 	{
// 		i = 0;
// 		while (result[i])
// 		{
// 			printf("Word %d: %s\n", i, result[i]);
// 			free(result[i]);
// 			i++;
// 		}
// 		free(result);
// 	}
// 	return 0;
// }