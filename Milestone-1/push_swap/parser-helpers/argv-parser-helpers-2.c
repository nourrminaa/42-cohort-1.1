/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv-parser-helpers-2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaarour <szaarour@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:00:00 by szaarour          #+#    #+#             */
/*   Updated: 2026/01/25 12:00:00 by szaarour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*join_arguments(char **argv, int argc, int start)
{
	char	*joined;
	int		i;

	if (!argv || start >= argc)
		show_error();
	joined = NULL;
	i = start;
	while (i < argc)
	{
		if (joined == NULL)
			joined = ft_strjoin_space(NULL, argv[i]);
		else
			joined = ft_strjoin_space(joined, argv[i]);
		i++;
	}
	if (!joined)
		show_error();
	return (joined);
}

int	validate_and_count(char **split)
{
	int	n;

	n = 0;
	while (split[n])
	{
		if (!check_non_digit(split[n]))
		{
			free_split(split);
			show_error();
		}
		n++;
	}
	return (n);
}

int	*fill_array(char **split, int n)
{
	int	*arr;
	int	i;

	arr = (int *)malloc(sizeof(int) * n);
	if (!arr)
	{
		free_split(split);
		show_error();
	}
	i = 0;
	while (i < n)
	{
		arr[i] = atoi_arg(split[i], arr, split);
		i++;
	}
	return (arr);
}
