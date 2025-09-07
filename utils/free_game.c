/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:29:24 by hkhairi           #+#    #+#             */
/*   Updated: 2025/09/07 19:23:28 by hkhairi          ###   ########.fr       */
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
	game->img_player = NULL;
}

void	free_doors(t_game *game)
{
	t_door	*tmp;

	if (!game->doors)
		return ;
	while (game->doors)
	{
		tmp = game->doors->next;
		free(game->doors);
		game->doors = tmp;
	}
}
