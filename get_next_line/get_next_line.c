/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:57:47 by hkhairi           #+#    #+#             */
/*   Updated: 2025/07/02 15:39:35 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

size_t	ft_strlen_line(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

static char	*get_line(int fd, char *line)
{
	char	*buffer;
	ssize_t	count_bytes;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	count_bytes = 1;
	while (!ft_strchr_line(line, '\n') && count_bytes > 0)
	{
		count_bytes = read(fd, buffer, BUFFER_SIZE);
		if (count_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[count_bytes] = '\0';
		if (!line)
			line = ft_strdup_line("");
		line = ft_strjoin_line(line, buffer);
	}
	free(buffer);
	return (line);
}

t_gnl	get_and_update_line(char *line)
{
	t_gnl	str;

	str.return_line = extract_first_line(line);
	str.new_line = update_remaining_line(line);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*line;
	t_gnl		str;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	line = get_line(fd, line);
	if (!line)
		return (NULL);
	str = get_and_update_line(line);
	line = str.new_line;
	return (str.return_line);
}
