/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:00:00 by szaarour          #+#    #+#             */
/*   Updated: 2026/01/25 18:10:29 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	sort_three_case(t_stack *a, int case_num, int *op_count)
{
	if (case_num == 1)
	{
		sa(a, op_count);
		rra(a, op_count);
	}
	else if (case_num == 2)
		ra(a, op_count);
	else if (case_num == 3)
	{
		sa(a, op_count);
		ra(a, op_count);
	}
	else if (case_num == 4)
		rra(a, op_count);
}

void	sort_three(t_stack *a, int *op_count)
{
	int	first;
	int	second;
	int	third;

	if (a->size != 3)
		return ;
	first = a->arr[0];
	second = a->arr[1];
	third = a->arr[2];
	if (first > second && second < third && first < third)
		sa(a, op_count);
	else if (first > second && second > third)
		sort_three_case(a, 1, op_count);
	else if (first > second && second < third)
		sort_three_case(a, 2, op_count);
	else if (first < second && second > third)
	{
		if (first < third)
			sort_three_case(a, 3, op_count);
		else
			sort_three_case(a, 4, op_count);
	}
}

static void	push_min_to_b(t_stack *a, t_stack *b, int *op_count)
{
	int	pos;
	int	dir;
	int	steps;

	pos = get_min_position(a);
	dir = shortest_rotation_direction(a, pos);
	steps = pos;
	if (dir == -1)
		steps = a->size - pos;
	while (steps-- > 0)
	{
		if (dir == 1)
			ra(a, op_count);
		else
			rra(a, op_count);
	}
	pb(a, b, op_count);
}

static void	sort_four_five(t_stack *a, t_stack *b, int *op_count)
{
	while (a->size > 3)
		push_min_to_b(a, b, op_count);
	sort_three(a, op_count);
	while (b->size > 0)
		pa(a, b, op_count);
}

void	sort_small(t_stack *a, t_stack *b, int *op_count)
{
	if (a->size == 2)
		sort_two(a, op_count);
	else if (a->size == 3)
		sort_three(a, op_count);
	else if (a->size == 4 || a->size == 5)
		sort_four_five(a, b, op_count);
}
