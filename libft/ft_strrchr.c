/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:31:38 by nmina             #+#    #+#             */
/*   Updated: 2025/11/15 01:07:42 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	ch;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	ch = (char)c;
	while (i >= 0)
	{
		if (s[i] == ch)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}

// #include <stdio.h>
// int main()
// {
// 	const char *str = "Hello, World!";
// 	int c = 'o';
// 	char *result = ft_strrchr(str, c);
// 	if (result)
// 		printf("Last occurrence of '%c': %s\n", c, result);
// 	else
// 		printf("Character '%c' not found.\n", c);
// 	return 0;
// }