/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:22:10 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 10:26:32 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	else if (dstsize <= dst_len)
		return (dstsize + src_len);
	else
	{
		i = 0;
		while (src[i] != '\0' && (dst_len + i) < (dstsize - 1))
		{
			dst[dst_len + i] = src[i];
			i++;
		}
		dst[dst_len + i] = '\0';
		return (dst_len + src_len);
	}
}

// #include <stdio.h>
// int main(){
// 	char dest[20] = "Hello, ";
// 	const char *src = "World!";
// 	size_t result;

// 	result = ft_strlcat(dest, src, sizeof(dest));
// 	printf("After strlcat:\n");
// 	printf("Destination: %s\n", dest);
// 	printf("Returned Length: %zu\n", result);

// 	// Test with smaller buffer
// 	char small_dest[10] = "Hello, ";
// 	result = ft_strlcat(small_dest, src, sizeof(small_dest));
// 	printf("After strlcat with small buffer:\n");
// 	printf("Small Destination: %s\n", small_dest);
// 	printf("Returned Length: %zu\n", result);

// 	return 0;
// }