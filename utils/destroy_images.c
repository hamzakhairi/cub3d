/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_images.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 19:23:00 by hkhairi           #+#    #+#             */
/*   Updated: 2025/09/07 19:24:38 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	destroy_tex(t_game *game, t_tex *tex)
{
	if (tex)
	{
		if (tex->img)
			mlx_destroy_image(game->mlx_ptr, tex->img);
		free(tex);
	}
}

void	destroy_images(t_game *game)
{
	if (game->img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->img_ptr);
	destroy_tex(game, game->img_north);
	destroy_tex(game, game->img_south);
	destroy_tex(game, game->img_west);
	destroy_tex(game, game->img_east);
	destroy_tex(game, game->img_door);
}
