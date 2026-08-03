/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:41:48 by nmina             #+#    #+#             */
/*   Updated: 2025/11/03 14:22:00 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

// int main()
// {
//     char ch = 'A';
//     char nl = '1';
//     write(1, &ch, 1);
//     if (ft_isalpha(ch))
//         write(1, " is an alphabetic character\n", 29);
//     else
//         write(1, " is not an alphabetic character\n", 33);
//     write(1, &nl, 1);
//     if (ft_isalpha(nl))
//         write(1, " is an alphabetic character\n", 29);
//     else
//         write(1, " is not an alphabetic character\n", 33);
//     return 0;
// }