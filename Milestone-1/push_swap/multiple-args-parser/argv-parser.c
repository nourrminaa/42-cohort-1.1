/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv-parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:00:41 by szaarour          #+#    #+#             */
/*   Updated: 2026/01/25 18:01:38 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	*parse_numbers(char **argv, int argc, int start)
{
	int		n;
	int		*arr;
	char	*joined;
	char	**split;

	joined = join_arguments(argv, argc, start);
	split = ft_split(joined, ' ');
	free(joined);
	if (!split || !split[0])
	{
		free_split(split);
		show_error();
	}
	n = validate_and_count(split);
	arr = fill_array(split, n);
	free_split(split);
	check_duplicates_int(arr, n);
	return (arr);
}

static char	*join_args_loop(char **argv, int argc, int start)
{
	char	*joined;
	int		i;

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
	return (joined);
}

int	count_numbers(char **argv, int argc, int start)
{
	char	*joined;
	char	**split;
	int		n;

	joined = join_args_loop(argv, argc, start);
	if (!joined)
		return (0);
	split = ft_split(joined, ' ');
	free(joined);
	if (!split)
		return (0);
	n = 0;
	while (split[n])
		n++;
	free_split(split);
	return (n);
}

t_cmd	parse_arguments(int argc, char **argv)
{
	t_cmd	cmd;
	int		start;

	if (argc < 2)
		return ((t_cmd){NULL, 0, ADAPTIVE, 0});
	start = get_start(argv, argc);
	if (start >= argc)
		return ((t_cmd){NULL, 0, ADAPTIVE, 0});
	cmd.n = count_numbers(argv, argc, start);
	if (cmd.n <= 0)
		return ((t_cmd){NULL, 0, ADAPTIVE, 0});
	cmd.arr = parse_numbers(argv, argc, start);
	cmd.strat = get_strategy(argv, argc);
	cmd.bench = has_bench_flag(argv, argc);
	return (cmd);
}
