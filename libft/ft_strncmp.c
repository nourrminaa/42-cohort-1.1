/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 20:52:36 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 11:09:27 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

// #include <unistd.h>
// int main()
// {
// 	const char *str1 = "Hello, World!";
// 	const char *str2 = "Hello, Worle!";
// 	size_t n = 13;
// 	int result;

// 	result = ft_strncmp(str1, str2, n);
// 	if (result < 0)
// 		write(1, "str1 is less than str2\n", 24);
// 	else if (result > 0)
// 		write(1, "str1 is greater than str2\n", 27);
// 	else
// 		write(1, "str1 is equal to str2\n", 23);
// 	return 0;
// }