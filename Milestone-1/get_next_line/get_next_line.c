/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:27:10 by nmina             #+#    #+#             */
/*   Updated: 2025/12/30 19:47:28 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free_null(char *buf, char *leftover)
{
	free(buf);
	free(leftover);
	return (NULL);
}

static char	*ft_read_to_leftover(int fd, char *leftover)
{
	char	*buf;
	int		bytes_read;
	char	*temp;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while ((!leftover || !ft_strchr(leftover, '\n')) && bytes_read != 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (ft_free_null(buf, leftover));
		buf[bytes_read] = '\0';
		if (!leftover)
			leftover = ft_strdup("");
		temp = leftover;
		leftover = ft_strjoin(temp, buf);
		free(temp);
	}
	free(buf);
	return (leftover);
}

static char	*ft_extract_line(char *leftover)
{
	size_t	i;
	char	*line;

	if (!leftover || !leftover[0])
		return (NULL);
	i = 0;
	while (leftover[i] && leftover[i] != '\n')
		i++;
	if (leftover[i] == '\n')
		i++;
	line = ft_substr(leftover, 0, i);
	return (line);
}

static char	*ft_update_leftover(char *leftover)
{
	size_t	i;
	char	*new_leftover;

	i = 0;
	while (leftover[i] && leftover[i] != '\n')
		i++;
	if (!leftover[i])
	{
		free(leftover);
		return (NULL);
	}
	i++;
	new_leftover = ft_substr(leftover, i, ft_strlen(leftover) - i);
	free(leftover);
	return (new_leftover);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	leftover = ft_read_to_leftover(fd, leftover);
	if (!leftover)
		return (NULL);
	line = ft_extract_line(leftover);
	leftover = ft_update_leftover(leftover);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>

// int main(void)
// {
//     // int     fd;
//     char    *line;

//     // fd = open("test.txt", O_RDONLY);
//     while ((line = get_next_line(0)) != NULL)
//     {
//         printf("%s", line);
//         free(line);
//     }
//     // close(fd);
//     return (0);
// }