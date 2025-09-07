/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drow_texter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 09:56:45 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/09/07 19:15:49 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	get_tex_pixel(t_tex *tex, int x, int y)
{
	char	*dst;

	if (x < 0)
		x = 0;
	if (x >= tex->width)
		x = tex->width - 1;
	if (y < 0)
		y = 0;
	if (y >= tex->height)
		y = tex->height - 1;
	dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

t_tex	*get_wall_texture(t_game *game, int ray_index)
{
	int	wall_dir;

	wall_dir = game->map->wall_direction[ray_index];
	if (game->ray_valeu[ray_index] == 'D')
		return (game->img_door);
	if (wall_dir == 1)
		return (game->img_north);
	else if (wall_dir == 2)
		return (game->img_east);
	else if (wall_dir == 3)
		return (game->img_west);
	else if (wall_dir == 4)
		return (game->img_south);
	else
		return (game->img_north);
}

float	calculate_wall_hit_x(t_game *game, int ray_index, float distance)
{
	int		wall_dir;
	float	ray_angle;
	float	hit_x;
	float	hit_y;

	ray_angle = game->map->angle - game->fov / 2 \
	+ (ray_index * game->fov / WIDTH_3D);
	hit_x = game->player_pixl_x + distance * cosf(ray_angle);
	hit_y = game->player_pixl_y + distance * sinf(ray_angle);
	wall_dir = game->map->wall_direction[ray_index];
	if (wall_dir == 1 || wall_dir == 4)
		return (hit_x - floor(hit_x / SIZE) * SIZE);
	else
		return (hit_y - floor(hit_y / SIZE) * SIZE);
}

void	drow_line(t_game *game, int y, int x, t_tex *tex)
{
	int	color;

	while (y < HEIGHT_3D)
	{
		if (y < game->wall_top)
			put_pixel(game, x, y, (game->config->ceiling_color[0] << 16)
				| (game->config->ceiling_color[1] << 8)
				| game->config->ceiling_color[2]);
		else if (y <= game->wall_bottom)
		{
			if ((int)game->tex_y >= tex->height)
				game->tex_y = (float)tex->height - 1;
			if ((int)game->tex_y < 0)
				game->tex_y = 0.0f;
			color = get_tex_pixel(tex, (int)game->tex_x, (int)game->tex_y);
			put_pixel(game, x, y, color);
			game->tex_y += game->tex_step;
		}
		else
			put_pixel(game, x, y, (game->config->floor_color[0] << 16)
				| (game->config->floor_color[1] << 8)
				| game->config->floor_color[2]);
		y++;
	}
}

void	draw_line_height(t_game *game, int x)
{
	int		y;
	t_tex	*tex;
	float	wall_hit;

	y = 0;
	tex = get_wall_texture(game, x);
	wall_hit = calculate_wall_hit_x(game, x, game->map->dis[x]);
	game->tex_x = ((wall_hit / SIZE) * (float)tex->width);
	if ((int)game->tex_x < 0)
		game->tex_x = 0.0f;
	if ((int)game->tex_x >= tex->width)
		game->tex_x = (float)tex->width - 1;
	if (game->wall_height <= 0.0f)
		return ;
	game->tex_step = (float)tex->height / game->wall_height;
	if (game->wall_top < 0)
		game->tex_y = ((0 - (float)game->wall_top) * game->tex_step);
	else
		game->tex_y = 0;
	drow_line(game, y, x, tex);
}
