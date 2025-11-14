/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:27:45 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 10:28:57 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

// #include <stdio.h>
// int main(){
// 	const char *str = "Hello, World!";
// 	int ch = 'W';
// 	char *result = ft_strchr(str, ch);
// 	if (result)
// 		printf("Character '%c' found at position: %ld\n", ch, result - str);
// 	else
// 		printf("Character '%c' not found.\n", ch);
// 	return 0;
// }