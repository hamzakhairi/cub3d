/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_move_palyer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 09:56:10 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/09/05 09:56:29 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_ft(t_game *game, float y, float x, int i)
{
	float	mv;

	mv = sqrtf(powf(DST_W_P, 2) - (powf(DST_W_P, 2) / 2));
	if ((game->map->grid[(int)(y - DST_W_P) / SIZE][(int)x / SIZE] != 'D'
		&& game->map->grid[((int)y + DST_W_P) / SIZE][(int)x / SIZE] != 'D'
		&& game->map->grid[(int)y / SIZE][((int)x + DST_W_P) / SIZE] != 'D'
		&& game->map->grid[(int)y / SIZE][((int)x - DST_W_P) / SIZE] != 'D'
		&& game->map->grid[(int)(y - mv) / SIZE][(int)(x + mv) / SIZE] != 'D'
		&& game->map->grid[(int)(y + mv) / SIZE][(int)(x - mv) / SIZE] != 'D'
		&& game->map->grid[(int)(y - mv) / SIZE][(int)(x - mv) / SIZE] != 'D'
		&& game->map->grid[(int)(y + mv) / SIZE][(int)(x - mv) / SIZE] != 'D')
		|| (game->is_open_door))
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
