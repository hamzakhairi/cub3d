/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:42:19 by hkhairi           #+#    #+#             */
/*   Updated: 2025/09/01 11:07:04 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void init_config(t_config *config)
{
	int i;

	config->no_texture = NULL;
	config->so_texture = NULL;
	config->we_texture = NULL;
	config->ea_texture = NULL;
	config->check_duplicate = malloc(sizeof(int) * 7);
	i = 0;
	while (i < 6)
	{
		config->check_duplicate[i] = 0;
		i++;
	}
	config->check_duplicate[i] = -1;
	config->floor_color[0] = -1;
	config->floor_color[1] = -1;
	config->floor_color[2] = -1;
	config->ceiling_color[0] = -1;
	config->ceiling_color[1] = -1;
	config->ceiling_color[2] = -1;
}

void init_map(t_map *map)
{
	map->grid = NULL;
	map->width = -1;
	map->height = -1;
	map->iszoom = 0;
	map->player_size = 4;
	map->minimap_size = 100;
	map->prefix_palyer_x = 102;
	map->prefix_palyer_y = 102;
	map->scale = SCALE;
}

int init_struct(t_game *game)
{
	game->config = malloc(sizeof(t_config));
	if (!game->config)
		return (0);
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return (free(game->config), 0);
	game->player_x = -1;
	game->start_parcing_map = -1;
	game->player_y = -1;
	init_map(game->map);
	init_config(game->config);
	game->is_open_door = 0;
	return (1);
}
