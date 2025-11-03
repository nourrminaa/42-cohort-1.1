/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:45:54 by nmina             #+#    #+#             */
/*   Updated: 2025/11/03 14:21:08 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

// int main()
// {
//     char ch1 = 'A';
//     char ch2 = '5';
//     char ch3 = '#';

//     write(1, &ch1, 1);
//     if (ft_isalnum(ch1))
//         write(1, " is an alphanumeric character\n", 30);
//     else
//         write(1, " is not an alphanumeric character\n", 34);

//     write(1, &ch2, 1);
//     if (ft_isalnum(ch2))
//         write(1, " is an alphanumeric character\n", 30);
//     else
//         write(1, " is not an alphanumeric character\n", 34);

//     write(1, &ch3, 1);
//     if (ft_isalnum(ch3))
//         write(1, " is an alphanumeric character\n", 30);
//     else
//         write(1, " is not an alphanumeric character\n", 34);

//     return 0;
// }