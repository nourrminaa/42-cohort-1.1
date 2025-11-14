/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 23:23:00 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 10:40:25 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] && needle[j] && haystack[i
				+ j] == needle[j] && (i + j) < len)
			j++;
		if (!needle[j])
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// int main(){
// 	const char *haystack = "this is a simple string.";
// 	const char *needle = "simple";
// 	size_t len = 25;
// 	char *result;

// 	result = ft_strnstr(haystack, needle, len);
// 	if (result)
// 		printf("Found needle at position: %ld\n", result - haystack);
// 	else
// 		printf("Needle not found within the first %zu characters.\n", len);
// 	return 0;
// }