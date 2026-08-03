/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptive-algo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 19:48:02 by szaarour          #+#    #+#             */
/*   Updated: 2026/01/25 17:36:52 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

double	compute_disorder(t_stack stack)
{
	double	mistakes;
	double	total_pairs;
	int		i;
	int		j;

	mistakes = 0;
	total_pairs = 0;
	i = 0;
	if (stack.size < 2)
		return (0.0);
	while (i < stack.size - 1)
	{
		j = i + 1;
		while (j < stack.size)
		{
			total_pairs++;
			if (stack.arr[i] > stack.arr[j])
				mistakes++;
			j++;
		}
		i++;
	}
	return (mistakes / total_pairs);
}

void	sort_adaptive(t_stack **a, t_stack **b, int *op_count)
{
	double	disorder;

	disorder = compute_disorder(**a);
	if (disorder < 0.2)
		sort_insertion(a, b, op_count);
	else if (disorder < 0.5)
		sort_bucket(a, b, op_count);
	else
		sort_quick(a, b, op_count);
}
