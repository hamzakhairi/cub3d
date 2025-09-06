/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:36:54 by hkhairi           #+#    #+#             */
/*   Updated: 2025/09/06 15:36:20 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	check_door(t_game *game, int index, int i, int j)
{
	char	*str;
	int		x;

	str = game->map->grid[index];
	x = i + j;
	if ((x > 0)
		&& (str[x] == 'D')
		&& !((str[x - 1] == '1' && str[x + 1] && str[x + 1] == '1')
			|| (index > 0 && ft_strlen(game->map->grid[index - 1]) > x
				&& game->map->grid[index - 1][x] == '1'
			&& ft_strlen(game->map->grid[index + 1]) > x
			&& game->map->grid[index + 1][x] == '1')))
		return (ft_putendl_fd(ERROR_MAP, 2), 0);
	return (1);
}
