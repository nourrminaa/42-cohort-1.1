/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 00:25:10 by nmina             #+#    #+#             */
/*   Updated: 2025/11/14 13:22:44 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(int n)
{
	int	len;

	len = 0;
	if (n < 0)
		n = -n;
	else if (n == 0)
		return (1);
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	reverse_str(char *str)
{
	int		i;
	int		len;
	char	temp;

	i = 0;
	len = ft_strlen(str) - 1;
	while (i < len / 2)
	{
		temp = str[i];
		str[i] = str[len - i];
		str[len - i] = temp;
		i++;
	}
}

static void	fill_str(char *str, int n, int is_negative)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		str[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (is_negative)
		str[i++] = '-';
	str[i] = '\0';
	reverse_str(str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		is_negative;
	int		length;

	is_negative = 0;
	if (n == 0)
		return (ft_strdup("0"));
	else if (n < 0)
	{
		is_negative = 1;
		n = -n;
	}
	length = int_len(n) + is_negative;
	str = (char *)malloc((length + 1 + is_negative) * sizeof(char));
	if (!str)
		return (NULL);
	fill_str(str, n, is_negative);
	return (str);
}

// #include <stdio.h>
// int main(){
// 	int number = -12345;
// 	char *str = ft_itoa(number);
// 	if (str)
// 	{
// 		printf("Integer: %d\n", number);
// 		printf("String: %s\n", str);
// 		free(str);
// 	}
// 	return 0;
// }