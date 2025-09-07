/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_horizontal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:48:44 by hkhairi           #+#    #+#             */
/*   Updated: 2025/09/07 16:09:45 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	get_horizontal(t_game *game)
{
	float	yh_step;
	float	xh_step;

	yh_step = SIZE;
	if (game->map->ray_facing_up)
		yh_step *= -1;
	xh_step = SIZE / tanf(game->map->angle);
	if (game->map->ray_facing_left && xh_step > 0)
		xh_step *= -1;
	if (game->map->ray_facing_right && xh_step < 0)
		xh_step *= -1;
	game->map->y_horizontal += yh_step;
	game->map->x_horizontal += xh_step;
}

float	horizontal_door(t_game *game, int check_y, int xh)
{
	if (check_y >= 0 && check_y < (game->map->height / SIZE)
		&& xh < (int)ft_strlen(game->map->grid[check_y])
		&& game->map->grid[check_y] != NULL
		&& (game->map->grid[check_y][xh] == '1'
		|| game->map->grid[check_y][xh] == 'D'))
	{
		if (game->map->grid[check_y][xh] == '1')
		{
			game->ray_valeu_h = '1';
			return (sqrtf(powf(game->map->x_horizontal \
			- game->player_pixl_x, 2) \
			+ powf(game->map->y_horizontal - game->player_pixl_y, 2)));
		}
		else if (game->map->grid[check_y][xh] == 'D')
		{
			game->is_door_hy = check_y;
			game->is_door_hx = xh;
			game->ray_valeu_h = 'D';
			if (!v_get_doors(game, xh, check_y))
				return (sqrtf(powf(game->map->x_horizontal \
				- game->player_pixl_x, 2) \
				+ powf(game->map->y_horizontal - game->player_pixl_y, 2)));
		}
	}
	return (-1);
}

float	horizontal_wall(t_game *game)
{
	int		xh;
	int		yh;
	int		check_y;
	float	dst;

	while (1)
	{
		xh = (int)game->map->x_horizontal / SIZE;
		yh = (int)game->map->y_horizontal / SIZE;
		if (xh < 0 || yh < 0 || xh >= (game->map->width / SIZE)
			|| yh >= (game->map->height / SIZE)
			|| game->map->grid[yh] == NULL
			|| xh >= (int)ft_strlen(game->map->grid[yh]))
			break ;
		check_y = yh;
		if (game->map->ray_facing_up)
			check_y = yh - 1;
		dst = horizontal_door(game, check_y, xh);
		if (dst != -1)
			return (dst);
		get_horizontal(game);
	}
	return (INFINITY);
}
