/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:31:38 by nmina             #+#    #+#             */
/*   Updated: 2025/11/13 21:26:53 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ch;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	ch = (char *)c;
	while (i >= 0)
	{
		if (s[i] == (char)ch)
			return (&s[i]);
		i--;
	}
	return (NULL);
}
