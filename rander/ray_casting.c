/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:58:49 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/09/04 11:00:15 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	get_horizontal(t_game *game)
{
	float	yh_step;
	float	xh_step;

	yh_step = SIZE;
	if (game->map->RayFacingUp)
		yh_step *= -1;
	xh_step = SIZE / tanf(game->map->angle);
	if (game->map->RayFacingLeft && xh_step > 0)
		xh_step *= -1;
	if (game->map->RayFacingRight && xh_step < 0)
		xh_step *= -1;
	game->map->Y_horizontal += yh_step;
	game->map->X_horizontal += xh_step;
}

void	get_vertical(t_game *game)
{
	float	yv_step;
	float	xv_step;

	xv_step = SIZE;
	if (game->map->RayFacingLeft)
		xv_step *= -1;
	yv_step = SIZE * tanf(game->map->angle);
	if (game->map->RayFacingUp && yv_step > 0)
		yv_step *= -1;
	if (game->map->RayFacingDown && yv_step < 0)
		yv_step *= -1;
	game->map->X_vertical += xv_step;
	game->map->Y_vertical += yv_step;
}

void directoin_player(t_game *game)
{
    if (game->map->angle < 0)
		game->map->angle += 2 * M_PI;
    if (game->map->angle >= 2 * M_PI)
		game->map->angle -= 2 * M_PI;
    
    game->map->RayFacingDown = (game->map->angle > 0 && game->map->angle < M_PI);
    game->map->RayFacingUp = !game->map->RayFacingDown;
    game->map->RayFacingRight = (game->map->angle < M_PI / 2 || game->map->angle > 3 * M_PI / 2);
    game->map->RayFacingLeft = !game->map->RayFacingRight;
}

float	horizontal_wall(t_game *game)
{
	int	xh;
	int	yh;
	int	check_y;

	while (1)
	{
		xh = (int)game->map->X_horizontal / SIZE;
		yh = (int)game->map->Y_horizontal / SIZE;
		
		if (xh < 0 || yh < 0 || xh >= (game->map->width / SIZE) || yh >= (game->map->height / SIZE)
			|| game->map->grid[yh] == NULL || xh >= (int)strlen(game->map->grid[yh]))
			break ;
		check_y = yh;
		if (game->map->RayFacingUp)
			check_y = yh - 1;

		if (check_y >= 0 && check_y < (game->map->height / SIZE) && xh < (int)strlen(game->map->grid[check_y])
			&& game->map->grid[check_y] != NULL && (game->map->grid[check_y][xh] == '1'
			|| (game->map->grid[check_y][xh] == 'D' && !game->is_open_door)))
		{
			if (game->map->grid[check_y][xh] == '1')
				game->ray_valeu_h = '1';
			else
			{
				game->is_door_hy = check_y;
				game->is_door_hx = xh;
				game->dst_door_h = sqrtf(powf(game->map->X_horizontal - game->player_pixl_x, 2) + powf(game->map->Y_horizontal - game->player_pixl_y, 2));
				game->ray_valeu_h = 'D';
			}
			return (sqrtf(powf(game->map->X_horizontal - game->player_pixl_x, 2) + powf(game->map->Y_horizontal - game->player_pixl_y, 2)));
		}
		get_horizontal(game);
	}
	return (INFINITY);
}

float	vertical_wall(t_game *game)
{
	int	xv;
	int	yv;
	int	check_x;

	while (1)
	{
		xv = (int)game->map->X_vertical / SIZE;
		yv = (int)game->map->Y_vertical / SIZE;
		
		if (xv < 0 || yv < 0 || xv >= (game->map->width / SIZE) || yv >= (game->map->height / SIZE) || game->map->grid[yv] == NULL || xv >= (int)strlen(game->map->grid[yv]))
			break ;
		check_x = xv;
		if (game->map->RayFacingLeft)
			check_x = xv - 1;

		if (check_x >= 0 && check_x < (game->map->width / SIZE) && yv < (game->map->height / SIZE) &&
		    check_x < (int)strlen(game->map->grid[yv]) && (game->map->grid[yv][check_x] == '1' || (game->map->grid[yv][check_x] == 'D' && !game->is_open_door)))
		{
			if (game->map->grid[yv][check_x] == '1')
				game->ray_valeu_v = '1';
			else
			{
				game->is_door_vy = yv;
				game->is_door_vx = check_x;
				game->dst_door_v = sqrtf(powf(game->map->X_vertical - game->player_pixl_x, 2) + powf(game->map->Y_vertical - game->player_pixl_y, 2));
				game->ray_valeu_v = 'D';
			}
			return (sqrtf(powf(game->map->X_vertical - game->player_pixl_x, 2) + powf(game->map->Y_vertical - game->player_pixl_y, 2)));
		}
		get_vertical(game);
	}
	return (INFINITY);
}

float distance_palyer_wall(t_game *game, float dis_v, float dis_h, int ray_count)
{
    if (dis_v < dis_h)
    {
		game->is_door_x = game->is_door_vx;
		game->is_door_y = game->is_door_vy;
		game->dst_door = game->dst_door_v;
		game->ray_valeu[ray_count] = game->ray_valeu_v;
        if (game->map->RayFacingRight)
            game->map->wall_direction[ray_count] = 3;
        else
            game->map->wall_direction[ray_count] = 2;
        return dis_v;
    }
    else
    {
		game->is_door_x = game->is_door_hx;
		game->is_door_y = game->is_door_hy;
		game->dst_door = game->dst_door_h;
		game->ray_valeu[ray_count] = game->ray_valeu_h;
        if (game->map->RayFacingDown)
            game->map->wall_direction[ray_count] = 1;
        else
            game->map->wall_direction[ray_count] = 4;
        return dis_h;
    }
}

float	ray_casting(t_game *game, float ray_angle, int ray_count)
{
	float	dis_v;
	float	dis_h;
	float	temp_angle;


	temp_angle = game->map->angle;
	game->map->angle = ray_angle;
	directoin_player(game);
	game->map->Y_horizontal = (float)(((int)game->player_pixl_y / SIZE) * SIZE);
	if (game->map->RayFacingDown)
		game->map->Y_horizontal += SIZE;
	game->map->X_horizontal = game->player_pixl_x + (game->map->Y_horizontal - game->player_pixl_y) / tanf(ray_angle);
	dis_h = horizontal_wall(game);
	game->map->X_vertical = (float)(((int)game->player_pixl_x / SIZE) * SIZE);
	if (game->map->RayFacingRight)
		game->map->X_vertical += SIZE;
	game->map->Y_vertical = game->player_pixl_y + (game->map->X_vertical - game->player_pixl_x) * tanf(ray_angle);
	dis_v = vertical_wall(game);
	directoin_player(game);
	game->map->angle = temp_angle;
	return (distance_palyer_wall(game, dis_v, dis_h, ray_count));
}
