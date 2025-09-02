/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:22:55 by hkhairi           #+#    #+#             */
/*   Updated: 2025/09/02 22:27:43 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	set_null(void **arry, int number)
{
	int	i;

	i = 0;
	while (i < number)
	{
		arry[i] = NULL;
		i++;
	}
}

int	load_walk_images(t_game *game)
{
	int		i;
	int		w;
	int		h;
	char	*str;

	game->img_player->images_walk = malloc(sizeof(void *) * 42);
	if (!game->img_player->images_walk)
		return (0);
	game->img_player->images_counter_walk = 41;
	set_null(game->img_player->images_walk, 41);
	i = 0;
	while (i < game->img_player->images_counter_walk)
	{
		str = path_image_image(PATH_WLKING, i + 1);
		game->img_player->images_walk[i] = mlx_xpm_file_to_image(game->mlx_ptr,
				str, &w, &h);
		free(str);
		if (!game->img_player->images_walk[i])
			return (printf("Error Walk %d\n", i), 0);
		i++;
	}
	return (1);
}

int	load_shot_images(t_game *game)
{
	int		i;
	int		w;
	int		h;
	char	*str;

	game->img_player->images_shout = malloc(sizeof(void *) * 3);
	if (!game->img_player->images_shout)
		return (0);
	set_null(game->img_player->images_shout, 2);
	game->img_player->images_counter_shot = 2;
	i = 0;
	while (i < game->img_player->images_counter_shot)
	{
		str = path_image_image(PATH_SOTING, i + 1);
		game->img_player->images_shout[i] = mlx_xpm_file_to_image(game->mlx_ptr,
				str, &w, &h);
		free(str);
		if (!game->img_player->images_shout[i])
			return (printf("Error Shot %d\n", i), 0);
		i++;
	}
	return (1);
}

int	load_feed_images(t_game *game)
{
	int		i;
	int		w;
	int		h;
	char	*str;

	game->img_player->images_Feeding = malloc(sizeof(void *) * 42);
	if (!game->img_player->images_Feeding)
		return (0);
	set_null(game->img_player->images_Feeding, 41);
	game->img_player->images_counter_Feeding = 41;
	i = 0;
	while (i < game->img_player->images_counter_Feeding)
	{
		str = path_image_image(PATH_FEEDING, i + 1);
		game->img_player->images_Feeding[i] = mlx_xpm_file_to_image(
				game->mlx_ptr, str, &w, &h);
		free(str);
		if (!game->img_player->images_Feeding[i])
			return (printf("Error Feeding %d\n", i), 0);
		i++;
	}
	return (1);
}

int	loading_image(t_game *game)
{
	game->img_player->current_image = 0;
	if (!load_walk_images(game))
		return (free_walk_images(game), free(game->img_player), 0);
	if (!load_shot_images(game))
		return (free_shot_images(game),
			free_walk_images(game), free(game->img_player), 0);
	if (!load_feed_images(game))
		return (free_feed_images(game),
			free_shot_images(game), free_walk_images(game),
			free(game->img_player), 0);
	return (1);
}
