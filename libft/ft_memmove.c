/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:06 by nmina             #+#    #+#             */
/*   Updated: 2025/11/07 17:07:39 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*dest;
	const unsigned char	*source;

	if (dst == NULL && src == NULL)
		return (NULL);
	else if (len == 0)
		return (dst);
	else if (dst == src)
		return (dst);
	else if (dst < src)
		return (ft_memcpy(dst, src, len));
	else
	{
		dest = (unsigned char *)dst;
		source = (const unsigned char *)src;
		i = len;
		while (i > 0)
		{
			dest[i - 1] = source[i - 1];
			i--;
		}
	}
	return (dst);
}
