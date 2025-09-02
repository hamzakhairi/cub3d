/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:17:35 by hkhairi           #+#    #+#             */
/*   Updated: 2025/09/02 22:20:43 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char	*path_image_image(char *PRE_FIX, int n)
{
	int		len_prefix;
	char	*index_str;
	int		len_index;
	int		total_len;
	char	*str;

	len_prefix = ft_strlen(PRE_FIX);
	index_str = ft_itoa(n);
	if (!index_str)
		return (NULL);
	len_index = ft_strlen(index_str);
	total_len = len_prefix + len_index + 4;
	str = malloc(total_len + 1);
	if (!str)
	{
		free(index_str);
		return (NULL);
	}
	memcpy(str, PRE_FIX, len_prefix);
	memcpy(str + len_prefix, index_str, len_index);
	memcpy(str + len_prefix + len_index, ".xpm", 4);
	str[total_len] = '\0';
	free(index_str);
	return (str);
}

void	update_state(t_game *game)
{
	int	max_frames;

	game->img_player->frame++;
	if (game->img_player->frame >= SPEED)
	{
		game->img_player->frame = 0;
		game->img_player->current_image++;
		if (game->img_player->is_state == 0)
			max_frames = game->img_player->images_counter_walk;
		else if (game->img_player->is_state == 1)
			max_frames = game->img_player->images_counter_shot;
		else
			max_frames = game->img_player->images_counter_Feeding;
		if (game->img_player->current_image >= max_frames)
		{
			game->img_player->current_image = 0;
			game->img_player->is_state = 0;
		}
	}
}

void	render_images(t_game *game)
{
	if (game->img_player->is_state == 0)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->img_player->images_walk[game->img_player->current_image],
			(WIDTH_3D) / 2 - (WIDTH_3D / 4),
			(HEIGHT_3D - 400) + (HEIGHT_3D - 400) / 16);
	else if (game->img_player->is_state == 1)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->img_player->images_shout[game->img_player->current_image],
			(WIDTH_3D) / 2 - (WIDTH_3D / 4),
			(HEIGHT_3D - 400) + (HEIGHT_3D - 400) / 16);
	else
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->img_player->images_Feeding[game->img_player->current_image],
			(WIDTH_3D) / 2 - (WIDTH_3D / 4),
			(HEIGHT_3D - 400) + (HEIGHT_3D - 400) / 16);
}

int	loop_inimation(t_game *game)
{
	create_put_image_to_window(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img_ptr, 0, 0);
	update_state(game);
	render_images(game);
	return (0);
}
