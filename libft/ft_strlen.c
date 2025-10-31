/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:24:21 by nmina             #+#    #+#             */
/*   Updated: 2025/10/31 14:53:44 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include<unistd.h>
// #include<stdio.h>
int	ft_strlen(const char *s)
{
	int	length;

	length = 0;
	while (s[length] != '\0')
	{
		length++;
	}
	return (length);
}

// int main(void)
// {
//     const char str[] = "hi! it's nour";
//     int length;

//     length = ft_strlen(str);
//     printf("Length: %d\n", length);
//     return 0;
// }