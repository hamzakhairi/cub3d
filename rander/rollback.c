/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rollback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:21:15 by hkhairi           #+#    #+#             */
/*   Updated: 2025/09/06 16:26:59 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	free_walk_images(t_game *game)
{
	int	i;

	if (!game->img_player || !game->img_player->images_walk)
		return ;
	i = 0;
	while (i < game->img_player->images_counter_walk)
	{
		if (game->img_player->images_walk[i])
			mlx_destroy_image(game->mlx_ptr, game->img_player->images_walk[i]);
		i++;
	}
	free(game->img_player->images_walk);
	game->img_player->images_walk = NULL;
}

void	free_shot_images(t_game *game)
{
	int	i;

	if (!game->img_player || !game->img_player->images_shout)
		return ;
	i = 0;
	while (i < game->img_player->images_counter_shot)
	{
		if (game->img_player->images_shout[i])
			mlx_destroy_image(game->mlx_ptr, game->img_player->images_shout[i]);
		i++;
	}
	free(game->img_player->images_shout);
	game->img_player->images_shout = NULL;
}

void	free_feed_images(t_game *game)
{
	int	i;

	if (!game->img_player || !game->img_player->images_feeding)
		return ;
	i = 0;
	while (i < game->img_player->images_counter_feeding)
	{
		if (game->img_player->images_feeding[i])
			mlx_destroy_image(game->mlx_ptr,
				game->img_player->images_feeding[i]);
		i++;
	}
	free(game->img_player->images_feeding);
	game->img_player->images_feeding = NULL;
}
