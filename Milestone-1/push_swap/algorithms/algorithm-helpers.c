/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bucket-sort-helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaarour <szaarour@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 01:21:42 by szaarour          #+#    #+#             */
/*   Updated: 2026/01/25 01:21:42 by szaarour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	push_back(t_stack *a, t_stack *b, int *op_count)
{
	int	pos;
	int	dir;

	while (b->size > 0)
	{
		pos = get_max_position(b);
		dir = shortest_rotation_direction(b, pos);
		if (dir == 1)
		{
			while (pos > 0)
			{
				rb(b, op_count);
				pos--;
			}
		}
		else
		{
			while (pos < b->size)
			{
				rrb(b, op_count);
				pos++;
			}
		}
		pa(a, b, op_count);
	}
}

int	*get_sorted_copy(const t_stack *a)
{
	int	*sorted;
	int	i;

	if (!a || a->size <= 0)
		return (NULL);
	sorted = (int *)malloc(sizeof(int) * a->size);
	if (!sorted)
		return (NULL);
	i = 0;
	while (i < a->size)
	{
		sorted[i] = a->arr[i];
		i++;
	}
	quick_sort(sorted, 0, a->size - 1);
	return (sorted);
}

void	index_with_sorted(t_stack *a, const int *sorted)
{
	int	i;
	int	j;

	if (!a || !sorted || a->size <= 0)
		return ;
	i = 0;
	while (i < a->size)
	{
		j = 0;
		while (j < a->size)
		{
			if (a->arr[i] == sorted[j])
			{
				a->arr[i] = j;
				break ;
			}
			j++;
		}
		i++;
	}
}

void	swap_int(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	get_max_bits(int max_index)
{
	int	bits;

	bits = 0;
	while ((1 << bits) <= max_index)
		bits++;
	return (bits);
}
