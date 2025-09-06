/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:57:01 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/09/06 20:01:42 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	image_3d(t_game *game)
{
	int		x;
	float	ray_angle;

	x = 0;
	game->distance_plane = (WIDTH_3D / 2) / tanf(game->fov / 2);
	while (x < WIDTH_3D)
	{
		ray_angle = game->map->angle - game->fov / 2 \
		+ (x * game->fov / WIDTH_3D);
		game->corrected_distance = game->map->dis[x] \
		* cosf(game->map->angle - ray_angle);
		if (game->corrected_distance < 0.1f)
			game->corrected_distance = 0.1f;
		game->wall_height = (SIZE / game->corrected_distance) \
		* game->distance_plane;
		if (game->wall_height > HEIGHT_3D * 3)
			game->wall_height = HEIGHT_3D * 3;
		game->wall_top = (HEIGHT_3D / 2) - (game->wall_height / 2);
		game->wall_bottom = (HEIGHT_3D / 2) + (game->wall_height / 2);
		draw_line_height(game, x);
		x++;
	}
}

void	setup_ray(t_game *game)
{
	float	ray_angle;
	float	angle_step;
	int		ray_count;

	ray_count = 0;
	angle_step = game->fov / WIDTH_3D;
	ray_angle = game->map->angle - game->fov / 2;
	game->is_door_vx = -1;
	game->is_door_vy = -1;
	game->is_door_hx = -1;
	game->is_door_hy = -1;
	while (ray_count < WIDTH_3D)
	{
		if (ray_angle < 0)
			ray_angle += 2 * M_PI;
		if (ray_angle >= 2 * M_PI)
			ray_angle -= 2 * M_PI;
		game->map->dis[ray_count] = ray_cast(game, ray_angle, ray_count);
		ray_angle += angle_step;
		ray_count++;
	}
	image_3d(game);
}
