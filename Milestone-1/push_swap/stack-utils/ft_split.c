/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:00:00 by szaarour          #+#    #+#             */
/*   Updated: 2026/01/25 19:35:45 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	count_words_split(const char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i])
			count++;
		while (s[i] && !ft_isspace(s[i]))
			i++;
	}
	return (count);
}

static char	*get_word_split(const char *s, int start, int end)
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

static void	free_all_split(char **arr, int words_count)
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

static int	fill_words(char **arr, const char *s)
{
	int	i;
	int	start;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i] && !ft_isspace(s[i]))
		{
			start = i;
			while (s[i] && !ft_isspace(s[i]))
				i++;
			arr[count] = get_word_split(s, start, i);
			if (!arr[count])
				return (-1);
			count++;
		}
	}
	arr[count] = NULL;
	return (0);
}

char	**ft_split(char *str, char c)
{
	char	**arr;
	int		words_count;

	(void)c;
	if (!str)
		return (NULL);
	words_count = count_words_split(str);
	arr = (char **)malloc((words_count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	if (fill_words(arr, str) == -1)
	{
		free_all_split(arr, words_count);
		return (NULL);
	}
	return (arr);
}
