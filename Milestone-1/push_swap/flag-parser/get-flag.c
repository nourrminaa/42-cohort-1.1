/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get-flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 22:34:04 by szaarour          #+#    #+#             */
/*   Updated: 2026/01/25 17:52:45 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	get_start(char **argv, int argc)
{
	int	i;
	int	strategy_count;

	i = 1;
	strategy_count = 0;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "--simple") == 0
			|| ft_strcmp(argv[i], "--medium") == 0
			|| ft_strcmp(argv[i], "--complex") == 0
			|| ft_strcmp(argv[i], "--adaptive") == 0)
			strategy_count++;
		else if (!is_allowed_flag(argv[i]))
			break ;
		i++;
	}
	if (strategy_count > 1)
		show_error();
	return (i);
}

t_strategy	get_strategy(char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "--simple") == 0)
			return (SIMPLE);
		else if (ft_strcmp(argv[i], "--medium") == 0)
			return (MEDIUM);
		else if (ft_strcmp(argv[i], "--complex") == 0)
			return (COMPLEX);
		else if (ft_strcmp(argv[i], "--adaptive") == 0)
			return (ADAPTIVE);
		i++;
	}
	return (ADAPTIVE);
}

int	has_bench_flag(char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "--bench") == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	is_allowed_flag(char *s)
{
	if (!s)
		return (0);
	if (ft_strcmp(s, "--simple") == 0)
		return (1);
	if (ft_strcmp(s, "--medium") == 0)
		return (1);
	if (ft_strcmp(s, "--complex") == 0)
		return (1);
	if (ft_strcmp(s, "--adaptive") == 0)
		return (1);
	if (ft_strcmp(s, "--bench") == 0)
		return (1);
	return (0);
}
