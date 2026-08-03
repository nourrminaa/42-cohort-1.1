/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 22:24:35 by szaarour          #+#    #+#             */
/*   Updated: 2026/01/25 17:41:08 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	swap(t_stack *stack)
{
	int	temp;

	if (!stack || stack->size < 2)
		return ;
	temp = stack->arr[0];
	stack->arr[0] = stack->arr[1];
	stack->arr[1] = temp;
}

void	push(t_stack *from, t_stack *to)
{
	int	i;

	if (!from || !to || from->size == 0)
		return ;
	i = to->size;
	while (i > 0)
	{
		to->arr[i] = to->arr[i - 1];
		i--;
	}
	to->arr[0] = from->arr[0];
	to->size++;
	stack_pop(from);
}

void	rotate(t_stack *stack)
{
	int	first;
	int	i;

	if (!stack || stack->size < 2)
		return ;
	first = stack->arr[0];
	i = 0;
	while (i < stack->size - 1)
	{
		stack->arr[i] = stack->arr[i + 1];
		i++;
	}
	stack->arr[stack->size - 1] = first;
}

void	reverse_rotate(t_stack *stack)
{
	int	last;
	int	i;

	if (!stack || stack->size < 2)
		return ;
	last = stack->arr[stack->size - 1];
	i = stack->size - 1;
	while (i > 0)
	{
		stack->arr[i] = stack->arr[i - 1];
		i--;
	}
	stack->arr[0] = last;
}
