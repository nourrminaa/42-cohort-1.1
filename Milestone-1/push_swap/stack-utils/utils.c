/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 22:06:48 by szaarour          #+#    #+#             */
/*   Updated: 2026/01/25 17:51:18 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	free_stack(t_stack *stack)
{
	if (!stack)
		return ;
	if (stack->arr)
		free(stack->arr);
	stack->arr = NULL;
	stack->size = 0;
	stack->capacity = 0;
}

void	stack_pop(t_stack *stack)
{
	int	i;

	if (!stack || stack->size <= 0)
		return ;
	i = 1;
	while (i < stack->size)
	{
		stack->arr[i - 1] = stack->arr[i];
		i++;
	}
	stack->size--;
}

int	check_sort_order(t_stack *stack)
{
	int	i;

	if (!stack || stack->size <= 1)
		return (1);
	i = 1;
	while (i < stack->size)
	{
		if (stack->arr[i - 1] > stack->arr[i])
			return (0);
		i++;
	}
	return (1);
}

int	get_top(t_stack *stack)
{
	if (!stack || stack->size <= 0)
		return (0);
	return (stack->arr[0]);
}

t_stack	copy_stack(t_stack *original)
{
	t_stack	new_stack;
	int		i;

	new_stack.arr = NULL;
	new_stack.size = 0;
	new_stack.capacity = 0;
	if (!original || original->size <= 0 || !original->arr)
		return (new_stack);
	new_stack.size = original->size;
	new_stack.capacity = original->size;
	new_stack.arr = (int *)malloc(sizeof(int) * new_stack.capacity);
	if (!new_stack.arr)
		return (new_stack);
	i = 0;
	while (i < original->size)
	{
		new_stack.arr[i] = original->arr[i];
		i++;
	}
	return (new_stack);
}
