/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 11:06:00 by nmina             #+#    #+#             */
/*   Updated: 2026/01/19 11:41:14 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_ptr_hex(unsigned long nb)
{
	char	*hex;
	int		count;

	hex = "0123456789abcdef";
	count = 0;
	if (nb >= 16)
		count += ft_print_ptr_hex(nb / 16);
	ft_putchar_fd(hex[nb % 16], 1);
	count++;
	return (count);
}

int	ft_print_ptr(void *ptr)
{
	int	count;

	if (!ptr)
		return (ft_print_str("(nil)"));
	count = 0;
	count += ft_print_str("0x");
	count += ft_print_ptr_hex((unsigned long)ptr);
	return (count);
}
