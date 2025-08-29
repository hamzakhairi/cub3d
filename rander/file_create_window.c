/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_create_window.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:04:49 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/08/29 15:14:35 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int load_texture(t_game *game, t_tex *tex, char *path)
{
    int w, h;
    tex->img = mlx_xpm_file_to_image(game->mlx_ptr, path, &w, &h);
    if (!tex->img)
    {
        printf("Error loading %s\n", path);
        return (1);
    }
    tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
            &tex->line_len, &tex->endian);
    tex->width = w;
    tex->height = h;
	printf("h %d\n",tex->height);
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

void	ft_image_minimap(t_game *game, int width, int height)
{
	int	y;
	int	x;
	int	color;
	int	mini_size;

	y = 0;
	mini_size = SIZE / game->map->scale;
	if (game->map->grid[height][width] == '1')
		color = 0x0000FF;
	else
		color = 0x000000;
	while (y < mini_size)
	{
		x = 0;
		while (x < mini_size)
		{
			put_pixel(game,
				x + width * mini_size, y + height * mini_size, color);
			x++;
		}
		y++;
	}
}

void	setup_minimap_player(t_game *game)
{
	int	i;
	int	j;
	int	r;
	int	center_x;
	int	center_y;

	r = game->map->player_size;
	center_x = (game->player_pixl_x / game->map->scale);
	center_y = (game->player_pixl_y / game->map->scale);
	i = -r;
	while (i <= r)
	{
		j = -r;
		while (j <= r)
		{
			if (i * i + j * j <= r * r)
				put_pixel(game, center_x + j, center_y + i, 0x00FF0000);
			j++;
		}
		i++;
	}
}

void	create_put_image_to_window(t_game *game)
{
	int	width;
	int	height;

	setup_ray(game);
	height = 0;
	while (game->map->grid[height])
	{
		width = 0;
		while (game->map->grid[height][width])
		{
			ft_image_minimap(game, width, height);
			width++;
		}
		height++;
	}
	setup_minimap_player(game);
	setup1_ray(game);
}

int	create_image(t_game *game)
{
	game->img_ptr = mlx_new_image(game->mlx_ptr, WIDTH_3D, HEIGHT_3D);
	if (!game->img_ptr)
		return (1);
	game->addr = mlx_get_data_addr(game->img_ptr, &game->bits_per_pixel, &game->line_length, &game->endian);
	if (load_texture(game, &game->img_north, "texter/wall/wall_1.xpm"))
		return (1);
	if (load_texture(game, &game->img_east, "texter/wall/wall_2.xpm"))
		return (1);
	if (load_texture(game, &game->img_west, "texter/wall/wall_3.xpm"))
		return (1);
	if (load_texture(game, &game->img_south, "texter/wall/wall_4.xpm"))
		return (1);
	create_put_image_to_window(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img_ptr, 0, 0);
	return (0);
}
