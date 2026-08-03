/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 23:44:19 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 11:00:45 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	s1_len;
	char	*dup;

	if (!s1)
		return (NULL);
	s1_len = ft_strlen(s1);
	dup = (char *)malloc((s1_len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// #include <stdio.h>
// int main(){
// 	const char *original = "Hello, World!";
// 	char *copy = ft_strdup(original);
// 	printf("Original: %s\n", original);
// 	printf("Copy: %s\n", copy);
// 	free(copy);
// 	return 0;
// }