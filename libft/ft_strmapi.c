/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 01:04:07 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 11:09:10 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new_str;

	if (!s || !f)
		return (NULL);
	new_str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new_str[i] = f(i, s[i]);
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

// #include <stdio.h>
// char my_func(unsigned int index, char c)
// {
// 	return (c + index);
// }

// int main(){
// 	const char *str = "abcd";
// 	char *result;
// 	result = ft_strmapi(str, my_func);
// 	printf("Mapped String: '%s'\n", result);
// 	free(result);
// 	return 0;
// }