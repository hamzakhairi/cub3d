/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_palyer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 09:56:10 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/09/06 18:38:17 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_ft(t_game *game, float y, float x, int i)
{
	float	mv;

	(void)i;
	mv = sqrtf(powf(DST_W_P, 2) - (powf(DST_W_P, 2) / 2));
	if ((game->map->grid[(int)(y - DST_W_P) / SIZE][(int)x / SIZE] != 'D'
		&& game->map->grid[((int)y + DST_W_P) / SIZE][(int)x / SIZE] != 'D'
		&& game->map->grid[(int)y / SIZE][((int)x + DST_W_P) / SIZE] != 'D'
		&& game->map->grid[(int)y / SIZE][((int)x - DST_W_P) / SIZE] != 'D'
		&& game->map->grid[(int)(y - mv) / SIZE][(int)(x + mv) / SIZE] != 'D'
		&& game->map->grid[(int)(y + mv) / SIZE][(int)(x - mv) / SIZE] != 'D'
		&& game->map->grid[(int)(y - mv) / SIZE][(int)(x - mv) / SIZE] != 'D'
		&& game->map->grid[(int)(y + mv) / SIZE][(int)(x - mv) / SIZE] != 'D')
		|| (!(game->is_door_x != -1 && game->is_door_y != -1
			&& !v_get_doors(game, game->is_door_x, game->is_door_y))
		|| v_get_doors(game, game->player_x, game->player_y)))
	{
		return (0);
	}
	return (1);
}

int	move_player(t_game *game, float y, float x, int i)
{
	float	mv;

	mv = sqrtf(powf(DST_W_P, 2) - (powf(DST_W_P, 2) / 2));
	if (game->map->grid[(int)(y - DST_W_P) / SIZE][(int)x / SIZE] != '1'
		&& game->map->grid[((int)y + DST_W_P) / SIZE][(int)x / SIZE] != '1'
		&& game->map->grid[(int)y / SIZE][((int)x + DST_W_P) / SIZE] != '1'
		&& game->map->grid[(int)y / SIZE][((int)x - DST_W_P) / SIZE] != '1'
		&& game->map->grid[(int)(y - mv) / SIZE][(int)(x + mv) / SIZE] != '1'
		&& game->map->grid[(int)(y + mv) / SIZE][(int)(x - mv) / SIZE] != '1'
		&& game->map->grid[(int)(y - mv) / SIZE][(int)(x - mv) / SIZE] != '1'
		&& game->map->grid[(int)(y + mv) / SIZE][(int)(x - mv) / SIZE] != '1'
		&& !ft_ft(game, y, x, i))
	{
		game->player_pixl_x = x;
		game->player_pixl_y = y;
		return (0);
	}
	return (1);
}
