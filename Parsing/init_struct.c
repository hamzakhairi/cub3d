/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:42:19 by hkhairi           #+#    #+#             */
/*   Updated: 2025/09/07 16:52:11 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	init_config(t_config *config)
{
	int	i;

	config->no_texture = NULL;
	config->so_texture = NULL;
	config->we_texture = NULL;
	config->ea_texture = NULL;
	config->check_duplicate = malloc(sizeof(int) * 7);
	if (!config->check_duplicate)
		return (ft_putendl_fd(ERROR_ALOCATION, 2), 0);
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
	return (1);
}

void	init_map(t_map *map)
{
	map->grid = NULL;
	map->width = -1;
	map->height = -1;
	map->iszoom = 0;
	map->player_size = PLAYER_SIZE;
	map->minimap_size = 100;
	map->prefix_palyer_x = 102;
	map->prefix_palyer_y = 102;
}

void	init_win(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->img_ptr = NULL;
	game->addr = NULL;
	game->map = NULL;
	game->config = NULL;
	game->img_door = NULL;
	game->img_south = NULL;
	game->img_north = NULL;
	game->img_north = NULL;
	game->img_west = NULL;
}

int	init_game(t_game *game)
{
	game->img_door = malloc(sizeof(t_tex));
	if (!game->img_door)
		return (ft_putendl_fd(ERROR_ALOCATION, 2), 0);
	game->img_door->addr = NULL;
	game->img_door->img = NULL;
	game->img_south = malloc(sizeof(t_tex));
	if (!game->img_south)
		return (ft_putendl_fd(ERROR_ALOCATION, 2), 0);
	game->img_south->addr = NULL;
	game->img_south->img = NULL;
	game->img_north = malloc(sizeof(t_tex));
	if (!game->img_north)
		return (ft_putendl_fd(ERROR_ALOCATION, 2), 0);
	game->img_north->addr = NULL;
	game->img_north->img = NULL;
	game->img_west = malloc(sizeof(t_tex));
	if (!game->img_west)
		return (ft_putendl_fd(ERROR_ALOCATION, 2), 0);
	game->img_west->addr = NULL;
	game->img_west->img = NULL;
	game->img_east = malloc(sizeof(t_tex));
	if (!game->img_east)
		return (ft_putendl_fd(ERROR_ALOCATION, 2), 0);
	game->img_east->addr = NULL;
	game->img_east->img = NULL;
	game->player_x = -1;
	game->start_parcing_map = -1;
	game->player_y = -1;
	game->is_open_door = 0;
	game->new_x = 0;
	game->new_y = 0;
	game->fov = (VD * M_PI) / TABE;
	return (1);
}

void	init_player(t_player *img_player)
{
	img_player->images_feeding = NULL;
	img_player->images_walk = NULL;
	img_player->images_shout = NULL;
	img_player->frame = 0;
	img_player->is_state = 0;
}

int	init_struct(t_game *game)
{
	init_win(game);
	game->config = NULL;
	game->map = NULL;
	game->img_player = NULL;
	game->doors = NULL;
	game->config = malloc(sizeof(t_config));
	if (!game->config)
		return (ft_putendl_fd(ERROR_ALOCATION, 2), 0);
	if (!init_config(game->config))
		return (0);
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return (ft_putendl_fd(ERROR_ALOCATION, 2), 0);
	init_map(game->map);
	game->img_player = malloc(sizeof(t_player));
	if (!game->img_player)
		return (ft_putendl_fd(ERROR_ALOCATION, 2), 0);
	init_player(game->img_player);
	if (!init_game(game))
		return (0);
	return (1);
}
