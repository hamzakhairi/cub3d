/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_randering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:55:48 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/09/07 15:48:14 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	store_direction(t_game *game, int width, int height)
{
	game->player_pixl_x = game->player_x * SIZE + (SIZE / 2);
	game->player_pixl_y = game->player_y * SIZE + (SIZE / 2);
	if (game->map->grid[height][width] == 'N')
	{
		game->map->palyer = 'N';
		game->map->angle = (3 * M_PI) / 2;
	}
	else if (game->map->grid[height][width] == 'S')
	{
		game->map->palyer = 'S';
		game->map->angle = M_PI / 2;
	}
	else if (game->map->grid[height][width] == 'E')
	{
		game->map->palyer = 'E';
		game->map->angle = 0;
	}
	else if (game->map->grid[height][width] == 'W')
	{
		game->map->palyer = 'W';
		game->map->angle = M_PI;
	}
}

void	calculate_width_height(t_game *game)
{
	int	width;
	int	height;
	int	x;

	x = 0;
	height = 0;
	while (game->map->grid[height])
	{
		width = 0;
		while (game->map->grid[height][width])
		{
			if (game->map->grid[height][width] == 'N'
				|| game->map->grid[height][width] == 'S'
				|| game->map->grid[height][width] == 'E'
				|| game->map->grid[height][width] == 'W')
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

void	setup_game(t_game *game)
{
	setup_ray(game);
	setup_minimap(game);
	setup_player(game);
}

int	create_image(t_game *game)
{
	game->img_ptr = mlx_new_image(game->mlx_ptr, WIDTH_3D, HEIGHT_3D);
	if (!game->img_ptr)
		return (ft_putendl_fd(ERROR_IMAGE, 2), 1);
	game->addr = mlx_get_data_addr(game->img_ptr, &game->bits_per_pixel, \
		&game->line_length, &game->endian);
	if (load_texture(game, &game->img_north, game->config->no_texture))
		return (1);
	if (load_texture(game, &game->img_east, game->config->ea_texture))
		return (1);
	if (load_texture(game, &game->img_west, game->config->we_texture))
		return (1);
	if (load_texture(game, &game->img_south, game->config->so_texture))
		return (1);
	if (load_texture(game, &game->img_door, "texter/door/1.xpm"))
		return (1);
	setup_game(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img_ptr, 0, 0);
	return (0);
}

int	start_randering(t_game *game)
{
	calculate_width_height(game);
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (ft_putendl_fd(ERROR_INIT, 2), 1);
	if (!loading_image(game))
		return (1);
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIDTH_3D, HEIGHT_3D, "cub3D");
	if (!game->win_ptr)
		return (ft_putendl_fd(ERROR_WINDOW, 2), 1);
	if (create_image(game))
		return (1);
	mlx_hook(game->win_ptr, 2, 0, moving, game);
	mlx_hook(game->win_ptr, 6, 0L, mouse_move_player, game);
	mlx_loop_hook(game->mlx_ptr, loop_inimation, game);
	mlx_loop(game->mlx_ptr);
	return (0);
}
