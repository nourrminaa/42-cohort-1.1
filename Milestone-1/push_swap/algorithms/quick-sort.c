/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick-sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:33:53 by szaarour          #+#    #+#             */
/*   Updated: 2026/01/26 11:27:02 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	partition(int *arr, int low, int high)
{
	int	pivot;
	int	i;
	int	j;

	pivot = arr[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (arr[j] <= pivot)
		{
			i++;
			swap_int(&arr[i], &arr[j]);
		}
		j++;
	}
	swap_int(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void	quick_sort(int *arr, int low, int high)
{
	int	p;

	if (low < high)
	{
		p = partition(arr, low, high);
		quick_sort(arr, low, p - 1);
		quick_sort(arr, p + 1, high);
	}
}

void	radix_index_stack(t_stack *a)
{
	int	*sorted;

	sorted = get_sorted_copy(a);
	if (!sorted)
		return ;
	index_with_sorted(a, sorted);
	free(sorted);
}

void	sort_quick(t_stack **a, t_stack **b, int *op_count)
{
	int	size;
	int	max_bits;
	int	i;
	int	j;

	size = (*a)->size;
	radix_index_stack(*a);
	max_bits = get_max_bits(size - 1);
	i = 0;
	while (i < max_bits)
	{
		j = size;
		while (j-- > 0)
		{
			if ((((*a)->arr[0] >> i) & 1) == 0)
				pb(*a, *b, op_count);
			else
				ra(*a, op_count);
		}
		while ((*b)->size > 0)
			pa(*a, *b, op_count);
		i++;
	}
}
