/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:58:49 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/09/06 16:24:25 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

float	distance_palyer_wall(t_game *game, \
	float dis_v, float dis_h, int ray_count)
{
	if (dis_v < dis_h)
	{
		game->is_door_x = game->is_door_vx;
		game->is_door_y = game->is_door_vy;
		game->ray_valeu[ray_count] = game->ray_valeu_v;
		if (game->map->ray_facing_right)
			game->map->wall_direction[ray_count] = 3;
		else
			game->map->wall_direction[ray_count] = 2;
		return (dis_v);
	}
	else
	{
		game->is_door_x = game->is_door_hx;
		game->is_door_y = game->is_door_hy;
		game->ray_valeu[ray_count] = game->ray_valeu_h;
		if (game->map->ray_facing_down)
			game->map->wall_direction[ray_count] = 1;
		else
			game->map->wall_direction[ray_count] = 4;
		return (dis_h);
	}
	return (0);
}

void	directoin_player(t_game *game)
{
	if (game->map->angle < 0)
		game->map->angle += 2 * M_PI;
	if (game->map->angle >= 2 * M_PI)
		game->map->angle -= 2 * M_PI;
	game->map->ray_facing_down = (game->map->angle > 0
			&& game->map->angle < M_PI);
	game->map->ray_facing_up = !game->map->ray_facing_down;
	game->map->ray_facing_right = (game->map->angle < M_PI / 2
			|| game->map->angle > 3 * M_PI / 2);
	game->map->ray_facing_left = !game->map->ray_facing_right;
}

float	ray_cast(t_game *game, float ray_angle, int ray_count)
{
	float	dis_v;
	float	dis_h;
	float	temp_angle;

	temp_angle = game->map->angle;
	game->map->angle = ray_angle;
	directoin_player(game);
	game->map->y_horizontal = (float)(((int)game->player_pixl_y / SIZE) * SIZE);
	if (game->map->ray_facing_down)
		game->map->y_horizontal += SIZE;
	game->map->x_horizontal = game->player_pixl_x
		+ (game->map->y_horizontal - game->player_pixl_y) / tanf(ray_angle);
	dis_h = horizontal_wall(game);
	game->map->x_vertical = (float)(((int)game->player_pixl_x / SIZE) * SIZE);
	if (game->map->ray_facing_right)
		game->map->x_vertical += SIZE;
	game->map->y_vertical = game->player_pixl_y
		+ (game->map->x_vertical - game->player_pixl_x) * tanf(ray_angle);
	dis_v = vertical_wall(game);
	directoin_player(game);
	game->map->angle = temp_angle;
	return (distance_palyer_wall(game, dis_v, dis_h, ray_count));
}
