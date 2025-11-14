/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 21:33:53 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 10:38:57 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// int main(){
// 	const char *str1 = "Hello, World!";
// 	const char *str2 = "Hello, Worle!";
// 	size_t n = 13;
// 	int result;

// 	result = ft_memcmp(str1, str2, n);
// 	if (result < 0)
// 		printf("str1 is less than str2\n");
// 	else if (result > 0)
// 		printf("str1 is greater than str2\n");
// 	else
// 		printf("str1 is equal to str2\n");
// 	return 0;
// }