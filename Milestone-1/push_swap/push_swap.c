/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:00:00 by szaarour          #+#    #+#             */
/*   Updated: 2026/01/25 17:54:05 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	select_strategy(t_stack *a, t_stack *b, t_strategy strat, int *op_c)
{
	if (strat == SIMPLE)
		sort_insertion(&a, &b, op_c);
	else if (strat == MEDIUM)
		sort_bucket(&a, &b, op_c);
	else if (strat == COMPLEX)
		sort_quick(&a, &b, op_c);
	else
		sort_adaptive(&a, &b, op_c);
}

static void	init_stacks(t_stack *a, t_stack *b, int *arr, int n)
{
	a->arr = arr;
	a->size = n;
	a->capacity = n;
	b->arr = (int *)malloc(sizeof(int) * n);
	b->size = 0;
	b->capacity = n;
}

static void	init_op_count(int *op_count)
{
	int	i;

	i = 0;
	while (i < 11)
		op_count[i++] = 0;
}

int	main(int argc, char **argv)
{
	int			op_count[11];
	t_stack		a;
	t_stack		b;
	t_cmd		cmd;
	double		original_disorder;

	cmd = parse_arguments(argc, argv);
	if (cmd.n <= 0)
		return (0);
	init_stacks(&a, &b, cmd.arr, cmd.n);
	init_op_count(op_count);
	original_disorder = compute_disorder(a);
	if (!check_sort_order(&a))
	{
		if (a.size <= 5)
			sort_small(&a, &b, op_count);
		else
			select_strategy(&a, &b, cmd.strat, op_count);
	}
	if (cmd.bench)
		print_bench(op_count, cmd.strat, original_disorder);
	free(a.arr);
	free(b.arr);
	return (0);
}
