/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:58:49 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/08/31 22:26:13 by hkhairi          ###   ########.fr       */
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
    while (game->map->angle < 0)
		game->map->angle += 2 * M_PI;
    while (game->map->angle >= 2 * M_PI)
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
    int map_x, map_y;
    int max_grid_x, max_grid_y;
    
    max_grid_y = 0;
    while (game->map->grid[max_grid_y] != NULL)
        max_grid_y++;
    
    max_grid_x = 0;
    if (max_grid_y > 0)
        max_grid_x = strlen(game->map->grid[0]);

	while (1)
	{
		xh = (int)game->map->X_horizontal / SIZE;
		yh = (int)game->map->Y_horizontal / SIZE;
		
		map_x = xh;
        map_y = yh;
		
		if (xh < 0 || yh < 0 || xh >= (game->map->width / SIZE) || yh >= (game->map->height / SIZE) || map_y < 0 || map_y >= max_grid_y ||
            map_x < 0 || map_x >= max_grid_x || game->map->grid[map_y] == NULL || map_x >= (int)strlen(game->map->grid[map_y]))
			break ;
		check_y = yh;
		if (game->map->RayFacingUp)
			check_y = yh - 1;

		if (check_y >= 0 && check_y < (game->map->height / SIZE) && (game->map->grid[check_y][xh] == '1'
			|| (game->map->grid[check_y][xh] == 'D' && !game->is_open_door)))
		{
			if (game->map->grid[check_y][xh] == '1')
				game->ray_valeu_h = '1';
			else
				game->ray_valeu_h = 'D';
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

	int i, j, color, r;
    int center_x, center_y;
    int map_x, map_y;
    int max_grid_x, max_grid_y;
    
    max_grid_y = 0;
    while (game->map->grid[max_grid_y] != NULL)
        max_grid_y++;
    
    max_grid_x = 0;
    if (max_grid_y > 0)
        max_grid_x = strlen(game->map->grid[0]);

	while (1)
	{
		xv = (int)game->map->X_vertical / SIZE;
		yv = (int)game->map->Y_vertical / SIZE;

		map_x = xv;
        map_y = yv;
		
		if (xv < 0 || yv < 0 || xv >= (game->map->width / SIZE) || yv >= (game->map->height / SIZE) || map_y < 0 || map_y >= max_grid_y ||
            map_x < 0 || map_x >= max_grid_x || game->map->grid[map_y] == NULL || map_x >= (int)strlen(game->map->grid[map_y]))
			break ;
		check_x = xv;
		if (game->map->RayFacingLeft)
			check_x = xv - 1;
		if (check_x >= 0 && check_x < (game->map->width / SIZE) && (game->map->grid[yv][check_x] == '1'
			|| (game->map->grid[yv][check_x] == 'D' && !game->is_open_door)))
		{
			if (game->map->grid[yv][check_x] == '1')
				game->ray_valeu_v = '1';
			else
				game->ray_valeu_v = 'D';
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
		game->ray_valeu[ray_count] = game->ray_valeu_v;
        if (game->map->RayFacingRight)
            game->map->wall_direction[ray_count] = 3;
        else
            game->map->wall_direction[ray_count] = 2;
        return dis_v;
    }
    else
    {
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
	return (distance_palyer_wall(game, dis_v, dis_h, ray_count));
}
