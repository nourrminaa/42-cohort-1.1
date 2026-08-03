/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:10:37 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 10:24:11 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	else
	{
		i = 0;
		while (i < dstsize - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
		return (src_len);
	}
}

// #include <stdio.h>
// int main()
// {
// 	const char source[] = "Hello, World!";
// 	char destination[20];
// 	size_t result;

// 	result = ft_strlcpy(destination, source, sizeof(destination));
// 	printf("Source: %s\n", source);
// 	printf("Destination: %s\n", destination);
// 	printf("Returned Length: %zu\n", result);

// 	// smaller destination buffer test
// 	char small_dest[6];
// 	result = ft_strlcpy(small_dest, source, sizeof(small_dest));
// 	printf("Source: %s\n", source);
// 	printf("Small Destination: %s\n", small_dest);
// 	printf("Returned Length: %zu\n", result);

// 	return 0;
// }