/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 23:36:41 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 10:59:24 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count == 0 || size == 0)
		return (malloc(0));
	else if (count > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, count * size);
	return (ptr);
}

// #include <stdio.h>
// int main()
// {
// 	size_t count = 5;
// 	size_t size = sizeof(int);
// 	int *arr;
// 	size_t i;

// 	arr = (int *)ft_calloc(count, size);
// 	printf("after ft_calloc:\n");
// 	for (i = 0; i < count; i++)
// 		printf("arr[%zu] = %d\n", i, arr[i]);
// 	free(arr);
// 	return (0);
// }