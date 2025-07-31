/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:42:19 by hkhairi           #+#    #+#             */
/*   Updated: 2025/07/31 09:31:32 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub.h"

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
    map->dir_x = 0;
    map->dir_y = 0;
    // map->angle = 0;
    map->width = -1;
    map->height = -1;
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
    game->player_dir = -1;
    init_map(game->map);
    init_config(game->config);
    return (1);
}
