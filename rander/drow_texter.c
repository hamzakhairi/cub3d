/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drow_texter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 09:56:45 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/09/07 15:30:30 by hkhairi          ###   ########.fr       */
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
		return (&game->img_door);
	if (wall_dir == 1)
		return (&game->img_north);
	else if (wall_dir == 2)
		return (&game->img_east);
	else if (wall_dir == 3)
		return (&game->img_west);
	else if (wall_dir == 4)
		return (&game->img_south);
	else
		return (&game->img_north);
}

float	calculate_wall_hit_x(t_game *game, int ray_index, float distance)
{
	int		wall_dir;
	float	ray_angle;
	float	hit_x;
	float	hit_y;

	ray_angle = game->map->angle - game->fov / 2 + (ray_index * game->fov / WIDTH_3D);
	hit_x = game->player_pixl_x + distance * cosf(ray_angle);
	hit_y = game->player_pixl_y + distance * sinf(ray_angle);
	wall_dir = game->map->wall_direction[ray_index];
	if (wall_dir == 1 || wall_dir == 4)
		return (hit_x - floor(hit_x / SIZE) * SIZE);
	else
		return (hit_y - floor(hit_y / SIZE) * SIZE);
}

void	draw_line_height(t_game *game, int x)
{
	float	tex_step;
	int		y;
	t_tex	*tex;
	float	wall_hit;
	float	tex_x;
	float	tex_y;
	int		color;

	y = 0;
	tex = get_wall_texture(game, x);
	wall_hit = calculate_wall_hit_x(game, x, game->map->dis[x]);
	tex_x = ((wall_hit / SIZE) * (float)tex->width);
	if ((int)tex_x < 0)
		tex_x = 0.0f;
	if ((int)tex_x >= tex->width)
		tex_x = (float)tex->width - 1;
	if (game->wall_height <= 0.0f)
		return ;
	tex_step = (float)tex->height / game->wall_height;
	if (game->wall_top < 0)
		tex_y = ((0 - (float)game->wall_top) * tex_step);
	else
		tex_y = 0;
	while (y < HEIGHT_3D)
	{ 
		if (y < game->wall_top)
			put_pixel(game, x, y, game->config->ceiling_color[0] << 16
                  | game->config->ceiling_color[1] << 8
                  | game->config->ceiling_color[2]);
		else if (y <= game->wall_bottom)
		{
			if ((int)tex_y >= tex->height)
				tex_y = (float)tex->height - 1;
			if ((int)tex_y < 0)
				tex_y = 0.0f;
			color = get_tex_pixel(tex, (int)tex_x, (int)tex_y);
			put_pixel(game, x, y, color);
			tex_y += tex_step;
		}
		else
			put_pixel(game, x, y, game->config->floor_color[0]  << 16
                  | game->config->floor_color[1] << 8
                  | game->config->floor_color[2]);
		y++;
	}
}


// void	draw_line_height(t_game *game, int x)
// {
// 	float	tex_step;
// 	float	tex_pos;
// 	int		y;
// 	t_tex	*tex;
// 	float	wall_hit;
// 	int		tex_x;
// 	int		tex_y;
// 	int		color;

// 	tex_pos = 0;
// 	y = 0;
// 	tex = get_wall_texture(game, x);
// 	wall_hit = calculate_wall_hit_x(game, x, game->map->dis[x]);
// 	tex_x = (int)((wall_hit / SIZE) * tex->width);
// 	if (tex_x < 0)
// 		tex_x = 0;
// 	if (tex_x >= tex->width)
// 		tex_x = tex->width - 1;

// 	if (game->wall_top < 0)
// 		tex_pos = (0 - game->wall_top) * tex_step;

// 	if (game->wall_top < 0)
// 		game->wall_top = 0;

// 	if (game->wall_bottom >= HEIGHT_3D)
// 		game->wall_bottom = HEIGHT_3D - 1;

// 	tex_step = (float)tex->height / game->wall_height;
// 	while (y < HEIGHT_3D)
// 	{
// 		if (y < game->wall_top)
// 			put_pixel(game, x, y, 0xFF0000);
// 		else if (y <= game->wall_bottom)
// 		{
// 			tex_y = (int)tex_pos;
// 			if (tex_y >= tex->height)
// 				tex_y = tex->height - 1;
// 			if (tex_y < 0)
// 				tex_y = 0;
// 			color = get_tex_pixel(tex, tex_x, tex_y);
// 			put_pixel(game, x, y, color);
// 			tex_pos += tex_step;
// 		}
// 		else
// 			put_pixel(game, x, y, 0x8B4513);
// 		y++;
// 	}
// }
