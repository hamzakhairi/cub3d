/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:57:01 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/09/04 11:11:17 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int get_tex_pixel(t_tex *tex, int x, int y)
{
    char *dst;

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

t_tex *get_wall_texture(t_game *game, int ray_index)
{
    int wall_dir;

    wall_dir = game->map->wall_direction[ray_index];

	if (game->ray_valeu[ray_index] == 'D')
		return (&game->img_door);
	if (wall_dir == 1)
		return (&game->img_north);
	else if (wall_dir == 2)
		return (&game->img_east);
	else if (wall_dir == 3)
		return &game->img_west;
	else if (wall_dir == 4)
		return (&game->img_south);
	else
		return (&game->img_north);
}

float calculate_wall_hit_x(t_game *game, int ray_index, float distance)
{
    int     wall_dir;
    float   ray_angle;
    float   hit_x;
    float   hit_y;

    ray_angle = game->map->angle - FOV / 2 + (ray_index * FOV / WIDTH_3D);
    hit_x = game->player_pixl_x + distance * cosf(ray_angle);
    hit_y = game->player_pixl_y + distance * sinf(ray_angle);

    wall_dir = game->map->wall_direction[ray_index];
    if (wall_dir == 1 || wall_dir == 4)
        return (hit_x - floor(hit_x / SIZE) * SIZE);
    else
        return (hit_y - floor(hit_y / SIZE) * SIZE);
}


void draw_line_height(t_game *game, int x)
{
	int     draw_start;
	float   tex_step;
	float   tex_pos;
	int     draw_end;
    int     y;
    t_tex   *tex;
    float   wall_hit;
    int     tex_x;

    tex = get_wall_texture(game, x);
    y = 0;
    wall_hit = calculate_wall_hit_x(game, x, game->map->dis[x]);
    tex_x = (int)((wall_hit / SIZE) * tex->width);
    
    if (tex_x < 0)
		tex_x = 0;
    if (tex_x >= tex->width)
		tex_x = tex->width - 1;

	if (game->wall_top < 0)
		draw_start = 0;
	else
		draw_start = game->wall_top;
	
	if (game->wall_bottom >= HEIGHT_3D)
		draw_end = HEIGHT_3D - 1;
	else
		draw_end = game->wall_bottom;

    tex_step = (float)tex->height / game->wall_height;
    tex_pos = 0;
    if (game->wall_top < 0)
        tex_pos = (0 - game->wall_top) * tex_step;
    
    while (y < HEIGHT_3D)
    {
        if (y < draw_start)
            put_pixel(game, x, y, 0xFF0000);
        else if (y <= draw_end)
        {
            int tex_y = (int)tex_pos;

            if (tex_y >= tex->height)
				tex_y = tex->height - 1;
            if (tex_y < 0)
				tex_y = 0;

            int color = get_tex_pixel(tex, tex_x, tex_y);
            put_pixel(game, x, y, color);

            tex_pos += tex_step;

        }
        else
            put_pixel(game, x, y, 0x8B4513);
        y++;
    }
}



void image_3d(t_game *game)
{
    int     x;
    float   ray_angle;

    x = 0;
    game->distance_plane = (WIDTH_3D / 2) / tanf(FOV / 2);
    
    while (x < WIDTH_3D)
    {
        ray_angle = game->map->angle - FOV / 2 + (x * FOV / WIDTH_3D);
        game->corrected_distance = game->map->dis[x] * cosf(game->map->angle - ray_angle);
        if (game->corrected_distance < 0.1f)
            game->corrected_distance = 0.1f;
        game->wall_height = (SIZE / game->corrected_distance) * game->distance_plane;
        if (game->wall_height > HEIGHT_3D * 3)
            game->wall_height = HEIGHT_3D * 3;
        game->wall_top = (HEIGHT_3D / 2) - (game->wall_height / 2);
        game->wall_bottom = (HEIGHT_3D / 2) + (game->wall_height / 2);
        draw_line_height(game, x);
        x++;
    }
}


void	setup_ray(t_game *game)
{
	float	ray_angle;
	float	angle_step;
	int		ray_count;

	ray_count = 0;
	angle_step = FOV / WIDTH_3D;
	ray_angle = game->map->angle - FOV / 2;
    game->is_door_vx = -1;
    game->is_door_vy = -1;
    game->is_door_hx = -1;
    game->is_door_hy = -1;
    game->dst_door_h = -1;
    game->dst_door_v = -1;
	while (ray_count < WIDTH_3D)
	{
		if (ray_angle < 0)
			ray_angle += 2 * M_PI;
		if (ray_angle >= 2 * M_PI)
			ray_angle -= 2 * M_PI;
		game->map->dis[ray_count] = ray_casting(game, ray_angle, ray_count);
		ray_angle += angle_step;
		ray_count++;
	}
    printf("game->is_door_x    == %d      , game->is_door_y    == %d    ,game->dst_door == %f\n",game->is_door_x, game->is_door_y,game->dst_door);
	image_3d(game);
}

