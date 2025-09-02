/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheack_lines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 21:16:33 by hkhairi           #+#    #+#             */
/*   Updated: 2025/09/02 22:36:36 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_check_fl_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	check_direction(t_game *game, int index, int i, int j)
{
	char	*str;
	int		x;

	str = game->map->grid[index];
	x = i + j;
	if (x > 0 && ft_strchr("0NSWED", str[x]) && ft_strchr(" \t", str[x - 1]))
		return (ft_putendl_fd(ERROR_MAP, 2), 0);
	if (ft_strchr("0NSWED", str[x]) && ft_strchr(" \t", str[x + 1]))
		return (ft_putendl_fd(ERROR_MAP, 2), 0);
	if (ft_strchr("0NSWED", str[x])
		&& (index > 0
			&& ((ft_strlen(game->map->grid[index - 1]) > x
					&& ft_strchr(" \t", game->map->grid[index - 1][x]))
			|| ft_strlen(game->map->grid[index - 1]) < x)))
		return (ft_putendl_fd(ERROR_MAP, 2), 0);
	if (ft_strchr("0NSWED", str[x])
		&& (game->map->grid[index + 1]
			&& ((ft_strlen(game->map->grid[index + 1]) > x
					&& ft_strchr(" \t", game->map->grid[index + 1][x]))
			|| ft_strlen(game->map->grid[index + 1]) < x)))
		return (ft_putendl_fd(ERROR_MAP, 2), 0);
	return (1);
}

int	check_dir(char *str, int index, t_game *game)
{
	int	i;
	int	j;
	int	length;

	i = 0;
	j = 0;
	length = ft_strlen(str);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i + j])
	{
		if (!ft_strchr("\t 01NSWED", str[i + j]))
			return (ft_putendl_fd(ERROR_MAP, 2), 0);
		else if (str[i + j] != '1')
		{
			if (!check_direction(game, index, i, j))
				return (0);
		}
		j++;
	}
	return (1);
}

int	check_player_direction(t_game *game, int i, int *counter)
{
	int		j;
	char	*map;

	j = 0;
	map = game->map->grid[i];
	while (map[j])
	{
		if (ft_strchr("NSWE", map[j]))
		{
			game->player_x = j;
			game->player_y = i;
			(*counter)++;
			if (*counter != 1)
				return (ft_putendl_fd(ERROR_MAP, 2), 0);
		}
		j++;
	}
	return (1);
}

int	cheack_lines(t_game *game)
{
	int		i;
	int		count_player;
	char	**map;

	count_player = 0;
	map = game->map->grid;
	i = 0;
	while (map[i])
	{
		if ((i == 0 || map[i + 1] == NULL) && !ft_check_fl_line(map[i]))
			return (ft_putendl_fd(ERROR_MAP, 2), 0);
		else if (!check_dir(map[i], i, game))
			return (0);
		if (!check_player_direction(game, i, &count_player))
			return (0);
		i++;
	}
	if (count_player == 0)
		return (ft_putendl_fd(ERROR_MAP, 2), 0);
	return (1);
}
