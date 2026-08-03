/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bucket-sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:47:05 by szaarour          #+#    #+#             */
/*   Updated: 2026/01/25 17:49:12 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	index_stack(t_stack *a)
{
	int	*sorted;

	sorted = get_sorted_copy(a);
	if (!sorted)
		return ;
	index_with_sorted(a, sorted);
	free(sorted);
}

static void	push_buckets(t_stack *a, t_stack *b, int bucket_count, int *op_c)
{
	int	bucket_size;
	int	limit;
	int	total;

	total = a->size;
	bucket_size = total / bucket_count;
	if (bucket_size == 0)
		bucket_size = 1;
	limit = bucket_size;
	while (a->size > 0)
	{
		if (a->arr[0] < limit)
		{
			pb(a, b, op_c);
			if (b->size > 1 && b->arr[0] < limit - (bucket_size / 2))
				rb(b, op_c);
		}
		else
			ra(a, op_c);
		if (b->size >= limit && limit < total)
			limit += bucket_size;
	}
}

static int	get_bucket_count(int size)
{
	if (size <= 10)
		return (2);
	if (size <= 100)
		return (5);
	return (11);
}

void	bucket_sort(t_stack *a, t_stack *b, int *op_count)
{
	int	bucket_count;

	if (!a || a->size < 2)
		return ;
	index_stack(a);
	bucket_count = get_bucket_count(a->size);
	push_buckets(a, b, bucket_count, op_count);
	push_back(a, b, op_count);
}

void	sort_bucket(t_stack **a, t_stack **b, int *op_count)
{
	bucket_sort(*a, *b, op_count);
}
