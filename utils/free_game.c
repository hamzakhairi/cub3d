/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:29:24 by hkhairi           #+#    #+#             */
/*   Updated: 2025/09/02 22:30:35 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	free_config(t_config *config)
{
	if (config->no_texture)
		free(config->no_texture);
	if (config->so_texture)
		free(config->so_texture);
	if (config->we_texture)
		free(config->we_texture);
	if (config->ea_texture)
		free(config->ea_texture);
	if (config->check_duplicate)
		free(config->check_duplicate);
	free(config);
}

void	destroy_images(t_game *game)
{
	if (game->img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->img_ptr);
	if (game->img_north.img)
		mlx_destroy_image(game->mlx_ptr, game->img_north.img);
	if (game->img_east.img)
		mlx_destroy_image(game->mlx_ptr, game->img_east.img);
	if (game->img_west.img)
		mlx_destroy_image(game->mlx_ptr, game->img_west.img);
	if (game->img_south.img)
		mlx_destroy_image(game->mlx_ptr, game->img_south.img);
	if (game->img_door.img)
		mlx_destroy_image(game->mlx_ptr, game->img_door.img);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->grid)
	{
		while (map->grid[i])
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	free(map);
}

void	free_images_player(t_game *game)
{
	free_walk_images(game);
	free_shot_images(game);
	free_feed_images(game);
	free(game->img_player);
}

void	free_game(t_game *game)
{
	if (game->map)
		free_map(game->map);
	destroy_images(game);
	if (game->config)
		free_config(game->config);
	if (game->win_ptr)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		game->win_ptr = NULL;
	}
	if (game->img_player)
		free_images_player(game);
	free(game);
}
