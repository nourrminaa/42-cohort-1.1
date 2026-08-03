/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 11:08:10 by nmina             #+#    #+#             */
/*   Updated: 2025/12/27 22:32:05 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(unsigned int nb, int upper)
{
	char	*hex;
	int		count;

	if (upper)
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	count = 0;
	if (nb >= 16)
		count += ft_print_hex(nb / 16, upper);
	ft_putchar_fd(hex[nb % 16], 1);
	count++;
	return (count);
}
