/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:13:22 by nmina             #+#    #+#             */
/*   Updated: 2026/01/25 17:41:57 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	sa(t_stack *a, int *op_count)
{
	swap(a);
	write(1, "sa\n", 3);
	if (op_count)
		op_count[0]++;
}

void	sb(t_stack *b, int *op_count)
{
	swap(b);
	write(1, "sb\n", 3);
	if (op_count)
		op_count[1]++;
}

void	pa(t_stack *a, t_stack *b, int *op_count)
{
	push(b, a);
	write(1, "pa\n", 3);
	if (op_count)
		op_count[3]++;
}

void	pb(t_stack *a, t_stack *b, int *op_count)
{
	push(a, b);
	write(1, "pb\n", 3);
	if (op_count)
		op_count[4]++;
}

void	ra(t_stack *a, int *op_count)
{
	rotate(a);
	write(1, "ra\n", 3);
	if (op_count)
		op_count[5]++;
}
