/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 18:00:00 by nmina             #+#    #+#             */
/*   Updated: 2026/01/25 18:04:57 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	put_nbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
		put_nbr_fd(n / 10, fd);
	c = (n % 10) + '0';
	write(fd, &c, 1);
}

static void	print_disorder(double disorder)
{
	int	percent_int;
	int	decimal;

	percent_int = (int)(disorder * 100);
	decimal = (int)(disorder * 10000) % 100;
	write(2, "[bench] disorder: ", 18);
	put_nbr_fd(percent_int, 2);
	write(2, ".", 1);
	if (decimal < 10)
		write(2, "0", 1);
	put_nbr_fd(decimal, 2);
	write(2, "%\n", 2);
}

static void	print_strategy(t_strategy strat, double disorder)
{
	if (strat == SIMPLE)
		write(2, "[bench] strategy: Simple / O(n^2)\n", 34);
	else if (strat == MEDIUM)
		write(2, "[bench] strategy: Medium / O(n*sqrt(n))\n", 40);
	else if (strat == COMPLEX)
		write(2, "[bench] strategy: Complex / O(n log n)\n", 39);
	else
	{
		if (disorder < 0.2)
			write(2, "[bench] strategy: Adaptive / O(n^2)\n", 36);
		else if (disorder < 0.5)
			write(2, "[bench] strategy: Adaptive / O(n*sqrt(n))\n", 42);
		else
			write(2, "[bench] strategy: Adaptive / O(n log n)\n", 40);
	}
}

static void	print_op_counts(int *op_count)
{
	int	total;
	int	i;

	total = 0;
	i = 0;
	while (i < 11)
	{
		total += op_count[i];
		i++;
	}
	write(2, "[bench] total_ops: ", 19);
	put_nbr_fd(total, 2);
	write(2, "\n", 1);
	write(2, "[bench] sa: ", 12);
	put_nbr_fd(op_count[0], 2);
	write(2, " sb: ", 5);
	put_nbr_fd(op_count[1], 2);
	write(2, " ss: ", 5);
	put_nbr_fd(op_count[2], 2);
	write(2, " pa: ", 5);
	put_nbr_fd(op_count[3], 2);
	write(2, " pb: ", 5);
	put_nbr_fd(op_count[4], 2);
	write(2, "\n", 1);
}

void	print_bench(int *op_count, t_strategy strat, double disorder)
{
	print_disorder(disorder);
	print_strategy(strat, disorder);
	print_op_counts(op_count);
	write(2, "[bench] ra: ", 12);
	put_nbr_fd(op_count[5], 2);
	write(2, " rb: ", 5);
	put_nbr_fd(op_count[6], 2);
	write(2, " rr: ", 5);
	put_nbr_fd(op_count[7], 2);
	write(2, " rra: ", 6);
	put_nbr_fd(op_count[8], 2);
	write(2, " rrb: ", 6);
	put_nbr_fd(op_count[9], 2);
	write(2, " rrr: ", 6);
	put_nbr_fd(op_count[10], 2);
	write(2, "\n", 1);
}
