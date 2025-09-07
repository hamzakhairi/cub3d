/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wall_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 19:17:46 by hkhairi           #+#    #+#             */
/*   Updated: 2025/09/07 19:21:31 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

t_tex	*init_tex(void)
{
	t_tex	*tex;

	tex = malloc(sizeof(t_tex));
	if (!tex)
	{
		ft_putendl_fd(ERROR_ALOCATION, 2);
		return (NULL);
	}
	tex->img = NULL;
	tex->addr = NULL;
	return (tex);
}

int	init_game(t_game *game)
{
	game->img_door = init_tex();
	game->img_south = init_tex();
	game->img_north = init_tex();
	game->img_west = init_tex();
	game->img_east = init_tex();
	if (!game->img_door || !game->img_south || !game->img_north
		|| !game->img_west || !game->img_east)
		return (0);
	game->player_x = -1;
	game->player_y = -1;
	game->start_parcing_map = -1;
	game->is_open_door = 0;
	game->new_x = 0;
	game->new_y = 0;
	game->fov = (VD * M_PI) / TABE;
	return (1);
}
