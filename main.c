/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:11:48 by hkhairi           #+#    #+#             */
/*   Updated: 2025/09/07 19:21:53 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

int	ft_close_win(t_game *game)
{
	free_game(game);
	exit(0);
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
	free_doors(game);
	free(game);
}

int	main(int argc, char *argv[])
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (1);
	if (!init_struct(game))
		(free_game(game), exit(1));
	if (!start_parcing(argc, argv, game))
		(free_game(game), exit(1));
	if (!fetch_door(game))
		(free_game(game), exit(1));
	if (start_randering(game))
		(free_game(game), exit(1));
	free_game(game);
	return (0);
}
