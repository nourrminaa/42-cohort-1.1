/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 23:58:12 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 11:04:10 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	size_t	len;
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	joined = (char *)malloc((len + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	while (*s1)
		joined[i++] = *s1++;
	while (*s2)
		joined[i++] = *s2++;
	joined[i] = '\0';
	return (joined);
}

// #include <stdio.h>
// int main(){
// 	const char *str1 = "Hello, ";
// 	const char *str2 = "World!";
// 	char *result;
// 	result = ft_strjoin(str1, str2);
// 	printf("Joined String: %s\n", result);
// 	free(result);
// 	return 0;
// }