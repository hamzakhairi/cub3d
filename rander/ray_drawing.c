/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:57:01 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/08/27 17:00:24 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	draw_line_height(t_game *game, int x)
{
	int	y;

	y = 0;
	while (y < HEIGHT_3D)
	{
		if (y < game->wall_top)
			put_pixel(game, x, y, 0xFF0000);
		else if (y < game->wall_top + game->wall_height)
		{
			if (game->map->wall_direction[x] == 1)
				put_pixel(game, x, y, 0x000000);//Black
			else if (game->map->wall_direction[x] == 2)
				put_pixel(game, x, y, 0xFFFFFF);//White
			else if ((int)game->map->wall_direction[x] == 3)
				put_pixel(game, x, y, 0x0000FF);//Blue
			else if ((int)game->map->wall_direction[x] == 4)
				put_pixel(game, x, y, 0x00FF00);//green
		}
		else
			put_pixel(game, x, y, 0x8B4513);
		y++;
	}
}

void	image_3d(t_game *game)
{
	int		x;
	float	cpy_angle;

	x = 0;
	game->distance_plane = (WIDTH_3D / 2) / tanf(FOV / 2);
	cpy_angle = game->map->angle - FOV / 2;
	x = 0;
	while (x < WIDTH_3D)
	{
		// Fix fisheye effect by using perpendicular distance
		game->corrected_distance = game->map->dis[x] * cosf(game->map->angle - (game->map->angle - FOV / 2 + (x * FOV / WIDTH_3D)));
		game->wall_height = (SIZE / game->corrected_distance)
			* game->distance_plane;
		game->wall_top = (HEIGHT_3D / 2) - (game->wall_height / 2);
		game->wall_bottom = (HEIGHT_3D / 2) + (game->wall_height / 2);
		if (game->wall_top < 0)
			game->wall_top = 0;
		if (game->wall_bottom >= HEIGHT_3D)
			game->wall_bottom = HEIGHT_3D - 1;
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
	angle_step = FOV / WIDTH_3D;
	ray_angle = game->map->angle - FOV / 2;
	while (ray_count < WIDTH_3D)
	{
		if (ray_angle < 0)
			ray_angle += 2 * M_PI;
		if (ray_angle >= 2 * M_PI)
			ray_angle -= 2 * M_PI;
		game->map->dis[ray_count] = ray_casting(game, ray_angle, ray_count);
		ray_angle += angle_step;
		ray_count++;
	}
	image_3d(game);
}

void	setup1_ray(t_game *game)
{
    float	new_x;
	float	new_y;
	float	cpy_angle;
    float	i;
	int		face;
	float	angle_step;

	angle_step = FOV / WIDTH_3D;
	cpy_angle = game->map->angle - FOV / 2;
	while (cpy_angle <= game->map->angle + FOV / 2)
	{
		i = 1;
		new_x = game->player_pixl_x + (cosf(cpy_angle) * i);
		new_y = game->player_pixl_y + (sinf(cpy_angle) * i);
		while (1)
		{
			new_x = game->player_pixl_x + (cosf(cpy_angle) * i);
			if (game->map->grid[((int)new_y) / SIZE][((int)new_x) / SIZE] == '1')
				break ;
			new_y = game->player_pixl_y + (sinf(cpy_angle) * i);
			if (game->map->grid[((int)new_y) / SIZE][((int)new_x) / SIZE] == '1')
				break ;
			put_pixel(game, (int)new_x / game->map->scale, (int)new_y / game->map->scale, 0x00FFFF00);
			i++;
		}
		cpy_angle += angle_step;
	}
}
