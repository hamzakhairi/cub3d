/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_randering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:55:48 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/08/31 15:22:51 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	store_direction(t_game *game, int width, int height)
{
	if (game->map->grid[height][width] == 'N')
	{
		game->map->palyer = 'N';
		game->map->angle = (3 * M_PI) / 2;//270 degrees dwon
	}
	else if (game->map->grid[height][width] == 'S')
	{
		game->map->palyer = 'S';
		game->map->angle = M_PI / 2;//90 degrees up
	}
	else if (game->map->grid[height][width] == 'E')
	{
		game->map->palyer = 'E';
		game->map->angle = 0;//0 degrees left
	}
	else if (game->map->grid[height][width] == 'W')
	{
		game->map->palyer = 'W';
		game->map->angle = M_PI;// 180 degrees rigte¢
	}
}

void Calculate_width_height(t_game *game)
{
	int width;
	int height;
	int x;

	x = 0;
	height = 0;
	game->player_pixl_x = game->player_x * SIZE + (SIZE / 2);
	game->player_pixl_y = game->player_y * SIZE + (SIZE / 2);
	while (game->map->grid[height])
	{
		width = 0;
		while (game->map->grid[height][width])
		{
			if (game->map->grid[height][width] == 'N' || game->map->grid[height][width] == 'S'
				|| game->map->grid[height][width] == 'E' || game->map->grid[height][width] == 'W')
				store_direction(game, width, height);
			width++;
		}
		if (x < width)
			x = width;
		height++;
	}
	game->map->width = x * SIZE;
	game->map->height = height * SIZE;
}

int	create_window(t_game *game)
{
	Calculate_width_height(game);
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (ft_putendl_fd(ERROR_INIT, 2), 1);
	loading_image(game);
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIDTH_3D, HEIGHT_3D, "cub3D");
	if (!game->win_ptr)
		return (ft_putendl_fd(ERROR_WINDOW, 2), 1);
	if (create_image(game))
		return (1);
	create_put_image_to_window(game);
	mlx_hook(game->win_ptr, 2, 0, moving, game);
	mlx_hook(game->win_ptr, 6, 0L, mouse_move_player, game);
	mlx_loop_hook(game->mlx_ptr, loop_inimation, game);
	return (0);
}

int	start_randering(t_game *game)
{
	if (create_window(game))
		return (1);
	mlx_loop(game->mlx_ptr);
	return (0);
}
