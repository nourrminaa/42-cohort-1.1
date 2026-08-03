/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:18:59 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 10:00:02 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

// int main()
// {
// 	int test1 = ft_isascii(65);   // should return 1
// 	int test2 = ft_isascii(128);  // should return 0
// 	write(1, "Test 1 (65): ", 13);
// 	write(1, test1 ? "1\n" : "0\n", 2);
// 	write(1, "Test 2 (128): ", 15);
// 	write(1, test2 ? "1\n" : "0\n", 2);
// 	return 0;
// }