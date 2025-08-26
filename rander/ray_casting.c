/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:58:49 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/08/26 12:02:53 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void get_horizontal(t_game *game)
{
	float Yh_step;
	float Xh_step;

	Yh_step = SIZE;
	if(game->map->RayFacingUp)
		Yh_step *= -1;
	Xh_step = SIZE / tanf(game->map->angle);
	if(game->map->RayFacingLeft && Xh_step > 0)
		Xh_step *= -1;
	if(game->map->RayFacingRight && Xh_step < 0)
		Xh_step *= -1;

	game->map->Y_horizontal += Yh_step;
	game->map->X_horizontal += Xh_step;
}

void get_vertical(t_game *game)
{
	float Yv_step;
	float Xv_step;

	Xv_step = SIZE;
	if (game->map->RayFacingLeft)
		Xv_step *= -1;
	Yv_step = SIZE * tanf(game->map->angle);
	if (game->map->RayFacingUp && Yv_step > 0)
		Yv_step *= -1;
	if(game->map->RayFacingDown && Yv_step < 0)
		Yv_step *= -1;

	game->map->X_vertical += Xv_step;
	game->map->Y_vertical += Yv_step;
}

void directoin_player(t_game *game)
{
    game->map->RayFacingDown  = game->map->angle > 0 && game->map->angle < M_PI;
	game->map->RayFacingUp    = !game->map->RayFacingDown;
	game->map->RayFacingRight = game->map->angle < M_PI / 2 || game->map->angle > 3 * M_PI / 2;
	game->map->RayFacingLeft  = !game->map->RayFacingRight;
}

float horizontal_wall(t_game *game)
{
	while (1)
	{
		int Xh = (int)game->map->X_horizontal / SIZE;
		int Yh = (int)game->map->Y_horizontal / SIZE;
		if (Xh < 0 || Yh < 0 || Xh >= (game->map->width / SIZE) || Yh >= (game->map->height / SIZE))
			break;
		int checkY = Yh;
		if (game->map->RayFacingUp)
			checkY = Yh - 1;
		
		if (checkY >= 0 && checkY < (game->map->height / SIZE) && game->map->grid[checkY][Xh] == '1')
		{
			return (sqrtf(powf(game->map->X_horizontal - game->player_pixl_x, 2) + powf(game->map->Y_horizontal - game->player_pixl_y, 2)));
		}
		get_horizontal(game);
	}
	return(INFINITY);
}

float vertical_wall(t_game *game)
{
	while (1)
	{
		int Xv = (int)game->map->X_vertical / SIZE;
		int Yv = (int)game->map->Y_vertical / SIZE;

		if (Xv < 0 || Yv < 0 || Xv >= (game->map->width / SIZE) || Yv >= (game->map->height / SIZE))
			break;
		
		int checkX = Xv;
		if (game->map->RayFacingLeft)
			checkX = Xv - 1;
		
		if (checkX >= 0 && checkX < (game->map->width / SIZE) && game->map->grid[Yv][checkX] == '1')
		{
			return (sqrtf(powf(game->map->X_vertical - game->player_pixl_x, 2) + powf(game->map->Y_vertical - game->player_pixl_y, 2)));
		}
		get_vertical(game);
	}
	return(INFINITY);
}

float distance_palyer_wall(t_game *game, float dis_v, float dis_h, int ray_count)
{
	if (dis_v < dis_h)
	{	
		if (game->map->RayFacingUp && game->map->RayFacingRight)
			game->map->wall_direction[ray_count] = 2;
		else if (game->map->RayFacingUp && game->map->RayFacingLeft)
			game->map->wall_direction[ray_count] = 3;
		else if (game->map->RayFacingDown && game->map->RayFacingLeft)
			game->map->wall_direction[ray_count] = 3;
		else if (game->map->RayFacingDown && game->map->RayFacingRight)
			game->map->wall_direction[ray_count] = 2;
		return dis_v;
	}
	else
	{
		if (game->map->RayFacingUp)
			game->map->wall_direction[ray_count] = 1;
		else if (game->map->RayFacingDown)
			game->map->wall_direction[ray_count] = 4;
		return dis_h;
	}
}

float ray_casting(t_game *game, float ray_angle, int ray_count)
{
	float dis_v;
	float dis_h;
	float temp_angle;

	temp_angle = game->map->angle;
	game->map->angle = ray_angle;
	directoin_player(game);
	game->map->Y_horizontal = floorf(game->player_pixl_y / SIZE) * SIZE;
	if (game->map->RayFacingDown)
  		game->map->Y_horizontal += SIZE;
	game->map->X_horizontal = game->player_pixl_x + (game->map->Y_horizontal - game->player_pixl_y) / tanf(ray_angle);
	dis_h = horizontal_wall(game);
	game->map->X_vertical = floorf(game->player_pixl_x / SIZE) * SIZE;
	if (game->map->RayFacingRight)
		game->map->X_vertical += SIZE;
	game->map->Y_vertical = game->player_pixl_y + (game->map->X_vertical - game->player_pixl_x) * tanf(ray_angle);
	dis_v = vertical_wall(game);
	directoin_player(game);
	game->map->angle = temp_angle;
	game->map->wall_direction[ray_count] = 0;
	return (distance_palyer_wall(game, dis_v, dis_h, ray_count));
}
