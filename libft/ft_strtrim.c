/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 00:02:13 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 11:06:14 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start_idx;
	size_t	end_idx;
	size_t	i;
	char	*trimmed_str;

	if (!s1 || !set)
		return (NULL);
	start_idx = 0;
	while (s1[start_idx] && ft_strchr(set, s1[start_idx]))
		start_idx++;
	end_idx = ft_strlen(s1);
	while (end_idx > start_idx && ft_strchr(set, s1[end_idx - 1]))
		end_idx--;
	trimmed_str = (char *)malloc((end_idx - start_idx + 1) * sizeof(char));
	if (!trimmed_str)
		return (NULL);
	i = 0;
	while (start_idx < end_idx)
		trimmed_str[i++] = s1[start_idx++];
	trimmed_str[i] = '\0';
	return (trimmed_str);
}

// #include <stdio.h>
// int main(){
// 	const char *str = "  Hello, World!  ";
// 	const char *set = "! ";
// 	char *result;
// 	result = ft_strtrim(str, set);
// 	printf("Trimmed String: '%s'\n", result);
// 	free(result);
// 	return 0;
// }