/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:50:03 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 10:11:36 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t					i;
	unsigned char			*dest;
	const unsigned char		*source;

	i = 0;
	dest = (unsigned char *)dst;
	source = (const unsigned char *)src;
	while (i < n)
	{
		dest[i] = source[i];
		i++;
	}
	return (dst);
}

// #include <stdio.h>
// int main()
// {
// 	char src[] = "Hello, World!";
// 	char dest[20];

// 	printf("Before memcpy:\n");
// 	printf("Source: %s\n", src);
// 	printf("Destination: %s\n", dest);

// 	ft_memcpy(dest, src, 13);

// 	printf("After memcpy:\n");
// 	printf("Source: %s\n", src);
// 	printf("Destination: %s\n", dest);

// 	return 0;
// }