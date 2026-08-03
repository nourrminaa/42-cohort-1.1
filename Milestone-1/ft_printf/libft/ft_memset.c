/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:46:01 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 10:10:27 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)b;
	while (len > 0)
	{
		str[i] = (unsigned char)c;
		i++;
		len--;
	}
	return (b);
}

// #include <stdio.h>
// int main()
// {
// 	char arr[10] = "abcdefghi";
// 	printf("Before memset: %s\n", arr);
// 	ft_memset(arr, 'x', 5);
// 	printf("After memset: %s\n", arr);
// 	return 0;
// }
