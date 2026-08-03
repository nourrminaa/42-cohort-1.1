/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation-2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:05:15 by nmina             #+#    #+#             */
/*   Updated: 2026/01/25 18:05:24 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	is_overflow(long nb, int sign, char *s)
{
	if (*s)
		return (1);
	if (nb * sign > INT_MAX || nb * sign < INT_MIN)
		return (1);
	return (0);
}

int	atoi_arg(char *str, int *arr, char **split)
{
	long	nb;
	int		i;
	int		sign;

	if (!str || !str[0])
		show_error_free(arr, split);
	i = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
		sign = (str[i++] == '-') * -2 + 1;
	if (str[i] < '0' || str[i] > '9')
		show_error_free(arr, split);
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + (str[i++] - '0');
	if (is_overflow(nb, sign, &str[i]))
		show_error_free(arr, split);
	return ((int)(nb * sign));
}
