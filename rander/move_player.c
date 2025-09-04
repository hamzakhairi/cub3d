/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:50:49 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/09/04 13:29:09 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	player_rotation(t_game *game)
{
	if (game->map->key == KEY_LEFT)
		game->map->angle = game->map->angle - 0.1;
	else if (game->map->key == KEY_RIGHT)
		game->map->angle = game->map->angle + 0.1;
	if (game->map->angle >= 2 * M_PI)
		game->map->angle -= 2 * M_PI;
	if (game->map->angle < 0)
		game->map->angle += 2 * M_PI;
	return (0);
}

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

int	move_game(t_game *game, int i)
{
	float	new_x;
	float	new_y;

	if (game->map->key == KEY_S)
	{
		new_x = game->player_pixl_x - (cosf(game->map->angle) * i);
		new_y = game->player_pixl_y - (sinf(game->map->angle) * i);
	}
	else if (game->map->key == KEY_W)
	{
		new_x = game->player_pixl_x + (cosf(game->map->angle) * i);
		new_y = game->player_pixl_y + (sinf(game->map->angle) * i);
	}
	else if (game->map->key == KEY_A)
	{
		new_x = game->player_pixl_x + (sinf(game->map->angle) * i);
		new_y = game->player_pixl_y - (cosf(game->map->angle) * i);
	}
	else if (game->map->key == KEY_D)
	{
		new_x = game->player_pixl_x - (sinf(game->map->angle) * i);
		new_y = game->player_pixl_y + (cosf(game->map->angle) * i);
	}
	return (move_player(game, new_y, new_x, i));
}

void	key1(t_game *game, int *check)
{
	if (game->map->key == ESC)
		(free_game(game), exit(0));
	else if (game->map->key == KEY_T)
	{
		game->img_player->is_state = 1;
		game->img_player->current_image = 0;
		*check = 0;
	}
	else if (game->map->key == KEY_Q)
	{
		if (!game->is_open_door)
			game->is_open_door = 1;
		else
			game->is_open_door = 0;
		*check = 0;
	}
	else if (game->map->key == KEY_F)
	{
		game->img_player->is_state = 2;
		game->img_player->current_image = 0;
		*check = 0;
	}
}

void	key2(t_game *game, int *check)
{
	if (game->map->key == KEY_LEFT || game->map->key == KEY_RIGHT)
		*check = player_rotation(game);
	else if (game->map->key == KEY_ZOOM)
	{
		if (game->map->iszoom == 0)
		{
			game->map->player_size = 8;
			game->map->minimap_size = 250;
			game->map->prefix_palyer_x = WIDTH_3D / 2;
			game->map->prefix_palyer_y = HEIGHT_3D / 2;
			game->map->scale = 1;
			game->map->iszoom = 1;
		}
		else
		{
			game->map->player_size = PLAYER_SIZE;
			game->map->minimap_size = 100;
			game->map->prefix_palyer_x = 102;
			game->map->prefix_palyer_y = 102;
			game->map->scale = SCALE;
			game->map->iszoom = 0;
		}
		*check = 0;
	}
}

int	moving(int key, t_game *game)
{
	int		i;
	int		check;

	game->map->key = key;
	i = NUM_GAME_MOVES;
	while (i > 0)
	{
		if (game->map->key == ESC || game->map->key == KEY_T
			|| game->map->key == KEY_Q || game->map->key == KEY_F)
			key1(game, &check);
		else if (game->map->key == KEY_S || game->map->key == KEY_W
			|| game->map->key == KEY_A || game->map->key == KEY_D)
			check = move_game(game, i);
		else if (game->map->key == KEY_LEFT || game->map->key == KEY_RIGHT
			|| game->map->key == KEY_ZOOM)
			key2(game, &check);
		if (check == 0)
			break ;
		i--;
	}
	return (0);
}
