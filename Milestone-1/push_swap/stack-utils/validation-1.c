/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation-1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:00:00 by szaarour          #+#    #+#             */
/*   Updated: 2026/01/25 18:05:08 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	check_non_digit(char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_all_args(char **args, int start, int end)
{
	int	i;

	i = start;
	while (i < end)
	{
		if (!check_non_digit(args[i]))
			show_error();
		i++;
	}
	return (1);
}

int	check_duplicates_int(int *arr, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (arr[i] == arr[j])
			{
				free(arr);
				show_error();
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	show_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

void	show_error_free(int *arr, char **split)
{
	if (split)
		free_split(split);
	if (arr)
		free(arr);
	show_error();
}
