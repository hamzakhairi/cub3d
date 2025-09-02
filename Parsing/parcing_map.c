/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:10:02 by hkhairi           #+#    #+#             */
/*   Updated: 2025/09/02 22:17:13 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	get_map_length(char *path, int skip_lines)
{
	char	*line;
	int		length;
	int		i;
	int		fd;

	line = NULL;
	length = 0;
	i = 0;
	fd = open(path, O_RDONLY, 0644);
	if (fd < 0)
		return (ft_putendl_fd(NOT_FOUND, 2), -1);
	line = get_next_line(fd);
	while (i < skip_lines - 2 && line)
	{
		(free(line), line = get_next_line(fd));
		i++;
	}
	free(line);
	line = get_next_line(fd);
	while (line)
	{
		(free(line), length += 1);
		line = get_next_line(fd);
	}
	return (get_next_line(-1), close(fd), length);
}

int	skip_to_map(int fd, int limit)
{
	int		i;
	char	*line;

	i = 0;
	while (i < limit - 1)
	{
		line = get_next_line(fd);
		if (!line)
			return (0);
		free(line);
		i++;
	}
	return (1);
}

int	read_map_lines(int fd, t_game *game)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		game->map->grid[i] = ft_other_strdup(line);
		if (!game->map->grid[i])
			return (free(line), ft_putendl_fd(ERROR_MAP, 2), 0);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	game->map->grid[i] = NULL;
	return (1);
}

int	filling_map(t_game *game, char *path)
{
	int	fd;
	int	length;

	fd = open(path, O_RDONLY, 0644);
	if (fd < 0)
		return (ft_putendl_fd(NOT_FOUND, 2), 0);
	length = get_map_length(path, game->start_parcing_map);
	if (length == -1)
		return (0);
	game->map->grid = malloc(sizeof(char *) * (length + 1));
	if (!game->map->grid)
		return (close(fd), ft_putendl_fd(ERROR_ALOCATION, 2), 0);
	if (!skip_to_map(fd, game->start_parcing_map))
		return (close(fd), 0);
	if (!read_map_lines(fd, game))
		return (close(fd), 0);
	close(fd);
	return (1);
}
