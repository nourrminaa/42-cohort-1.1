/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion-sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:46:09 by nmina             #+#    #+#             */
/*   Updated: 2026/01/26 10:57:30 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	rotate_min_to_top(t_stack *a, int pos, int *op_count)
{
	int	size;

	size = a->size;
	if (pos <= size / 2)
	{
		while (pos > 0)
		{
			ra(a, op_count);
			pos--;
		}
	}
	else
	{
		pos = size - pos;
		while (pos > 0)
		{
			rra(a, op_count);
			pos--;
		}
	}
}

void	insertion_sort(t_stack *a, t_stack *b, int *op_count)
{
	int	pos;

	while (a->size > 0)
	{
		pos = get_min_position(a);
		rotate_min_to_top(a, pos, op_count);
		pb(a, b, op_count);
	}
	while (b->size > 0)
		pa(a, b, op_count);
}

void	sort_insertion(t_stack **a, t_stack **b, int *op_count)
{
	insertion_sort(*a, *b, op_count);
}
