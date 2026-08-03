/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:31:37 by nmina             #+#    #+#             */
/*   Updated: 2025/11/03 14:22:39 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// int main(void)
// {
//     char ch = '5';
//     char nl = '\n';
//     write(1, &ch, 1);
//     if (ft_isdigit(ch))
//         write(1, " is a digit\n", 13);
//     else
//         write(1, " is not a digit\n", 17);
//     write(1, &nl, 1);
//     if (ft_isdigit(nl))
//         write(1, " is a digit\n", 13);
//     else
//         write(1, " is not a digit\n", 17);
//     return 0;
// }