/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:54:17 by nmina             #+#    #+#             */
/*   Updated: 2025/11/03 14:23:46 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

// int main(void)
// {
//     char ch1 = 'A';
//     char ch2 = ' ';
//     char ch3 = '\n';

//     write(1, &ch1, 1);
//     if (ft_isprint(ch1))
//         write(1, " is a printable character\n", 26);
//     else
//         write(1, " is not a printable character\n", 30);

//     write(1, &ch2, 1);
//     if (ft_isprint(ch2))
//         write(1, " is a printable character\n", 26);
//     else
//         write(1, " is not a printable character\n", 30);

//     write(1, &ch3, 1);
//     if (ft_isprint(ch3))
//         write(1, " is a printable character\n", 26);
//     else
//         write(1, " is not a printable character\n", 30);

//     return 0;
// }