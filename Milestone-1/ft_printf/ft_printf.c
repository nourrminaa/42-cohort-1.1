/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:27:18 by nmina             #+#    #+#             */
/*   Updated: 2026/01/19 09:38:10 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_format(char c, va_list args)
{
	if (c == 'c')
		return (ft_print_char(va_arg(args, int)));
	else if (c == '%')
		return (ft_print_char('%'));
	else if (c == 's')
		return (ft_print_str(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_print_ptr(va_arg(args, void *)));
	else if (c == 'x')
		return (ft_print_hex(va_arg(args, unsigned int), 0));
	else if (c == 'X')
		return (ft_print_hex(va_arg(args, unsigned int), 1));
	else if (c == 'd' || c == 'i')
		return (ft_print_nbr(va_arg(args, int)));
	else if (c == 'u')
		return (ft_print_unsigned(va_arg(args, unsigned int)));
	else
		return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += ft_handle_format(*format, args);
		}
		else
			count += ft_print_char(*format);
		format++;
	}
	va_end(args);
	return (count);
}

// #include <stdio.h>
// #include "ft_printf.h"

// int main(void)
// {
// 	char *str = "test";
//     int return_value1, return_value2;

// 	ft_printf("--- printf ---\n");
// 	return_value1 = printf("%c %s %d %i %u %x %X %p %%\n", 
// 	'A', "hi", -42, 42, 42, 255, 255, str);
//     ft_printf("%c", '\n');

// 	ft_printf("--- ft_printf ---\n");
// 	return_value2 = ft_printf("%c %s %d %i %u %x %X %p %%\n",
// 	'A', "hi", -42, 42, 42, 255, 255, str);

//     ft_printf("--- Return Values ---\n");
//     ft_printf("Return value of printf: %d\n", return_value1);
//     ft_printf("Return value of ft_printf: %d\n", return_value2);
// 	return (0);
// }