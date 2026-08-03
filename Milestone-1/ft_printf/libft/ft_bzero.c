/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:50:39 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 10:09:31 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

// #include <stdio.h>
// int main()
// {
// 	char arr[10] = "abcdefghi";
// 	printf("Before bzero:\n%s\n", arr);
// 	ft_bzero(arr, 5);
// 	printf("After bzero: \n");
// 	for (int i = 0; i < 10; i++)
// 		printf("%d ", arr[i]);
// 	return 0;
// }