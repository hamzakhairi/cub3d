/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stup_minimap_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:04:49 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/09/07 11:00:06 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	load_texture(t_game *game, t_tex *tex, char *path)
{
	int	w;
	int	h;

	tex->img = mlx_xpm_file_to_image(game->mlx_ptr, path, &w, &h);
	if (!tex->img)
		return (ft_putendl_fd(ERROR_IMAGE_XPM, 2), 1);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	tex->width = w;
	tex->height = h;
	return (0);
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH_3D || y >= HEIGHT_3D)
		return ;
	dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	drow_minimap(t_game *game, int center_x, int center_y)
{
	int	color;
	int	map_x;
	int	map_y;

	color = 0;
	map_x = center_x / SIZE;
	map_y = center_y / SIZE;
	if (center_x < 0 || center_y < 0
		|| center_x >= game->map->width || center_y >= game->map->height
		|| map_y < 0 || map_y >= game->map->height / SIZE
		|| map_x < 0 || map_x >= game->map->width / SIZE
		|| game->map->grid[map_y] == NULL
		|| map_x >= (int)ft_strlen(game->map->grid[map_y]))
		color = 0x000000;
	else if (game->map->grid[map_y][map_x] == '1')
		color = 0x0000FF;
	else if (game->map->grid[map_y][map_x] == 'D' && !game->is_open_door)
		color = 0x00FF00;
	else if (game->map->grid[map_y][map_x] == '0'
		|| ft_strchr("NSWE", game->map->grid[map_y][map_x])
		|| (game->map->grid[map_y][map_x] == 'D' && game->is_open_door))
		color = 0xB2BEB5;
	else if (!ft_strchr("NWSE", game->map->grid[map_y][map_x]))
		color = 0x000000;
	return (color);
}

void	setup_minimap(t_game *game)
{
	int	i;
	int	j;
	int	r;
	int	center_x;
	int	center_y;

	r = game->map->minimap_size;
	i = -r;
	while (i <= r)
	{
		j = -r;
		while (j <= r)
		{
			if (i * i + j * j <= r * r)
			{
				center_x = ((int)game->player_pixl_x + j);
				center_y = ((int)game->player_pixl_y + i);
				put_pixel(game, game->map->prefix_palyer_x + j,
					game->map->prefix_palyer_y + i,
					drow_minimap(game, center_x, center_y));
			}
			j++;
		}
		i++;
	}
}

void	setup_player(t_game *game)
{
	int	i;
	int	j;
	int	r;

	r = game->map->player_size;
	i = -r;
	while (i <= r)
	{
		j = -r;
		while (j <= r)
		{
			if (i * i + j * j <= r * r)
				put_pixel(game, game->map->prefix_palyer_x + j,
					game->map->prefix_palyer_x + i, 0x00FF0000);
			j++;
		}
		i++;
	}
}
