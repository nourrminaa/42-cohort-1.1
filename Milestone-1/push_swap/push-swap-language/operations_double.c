/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_double.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:04:55 by nmina             #+#    #+#             */
/*   Updated: 2026/01/25 17:41:32 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ss(t_stack *a, t_stack *b, int *op_count)
{
	swap(a);
	swap(b);
	write(1, "ss\n", 3);
	if (op_count)
		op_count[2]++;
}

void	rr(t_stack *a, t_stack *b, int *op_count)
{
	rotate(a);
	rotate(b);
	write(1, "rr\n", 3);
	if (op_count)
		op_count[7]++;
}

void	rrr(t_stack *a, t_stack *b, int *op_count)
{
	reverse_rotate(a);
	reverse_rotate(b);
	write(1, "rrr\n", 4);
	if (op_count)
		op_count[10]++;
}
