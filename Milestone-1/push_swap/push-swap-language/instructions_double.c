/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_double.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:16:28 by nmina             #+#    #+#             */
/*   Updated: 2026/01/25 17:42:40 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	rb(t_stack *b, int *op_count)
{
	rotate(b);
	write(1, "rb\n", 3);
	if (op_count)
		op_count[6]++;
}

void	rra(t_stack *a, int *op_count)
{
	reverse_rotate(a);
	write(1, "rra\n", 4);
	if (op_count)
		op_count[8]++;
}

void	rrb(t_stack *b, int *op_count)
{
	reverse_rotate(b);
	write(1, "rrb\n", 4);
	if (op_count)
		op_count[9]++;
}
