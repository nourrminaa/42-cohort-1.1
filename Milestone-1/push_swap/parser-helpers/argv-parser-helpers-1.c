/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv-parser-helpers-1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:00:00 by szaarour          #+#    #+#             */
/*   Updated: 2026/01/25 17:59:57 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strdup_local(const char *s)
{
	char	*dup;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin_space(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!s1)
		return (ft_strdup_local(s2));
	if (!s2)
		return (s1);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!res)
		return (free(s1), NULL);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	res[i++] = ' ';
	j = -1;
	while (s2[++j])
		res[i++] = s2[j];
	res[i] = '\0';
	free(s1);
	return (res);
}
