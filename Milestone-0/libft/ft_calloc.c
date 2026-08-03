/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 23:36:41 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 13:47:26 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total_size;

	if (count == 0 || size == 0)
		return (malloc(1));
	total_size = count * size;
	if (count > SIZE_MAX / size)
		return (0);
	ptr = malloc(total_size);
	if (!ptr)
		return (0);
	ft_memset(ptr, 0, total_size);
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