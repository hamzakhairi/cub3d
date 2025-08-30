/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:57:01 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/08/30 16:37:04 by hkhairi          ###   ########.fr       */
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
    int wall_dir = game->map->wall_direction[ray_index];

	if (game->ray_valeu[ray_index] == 'D')
		return &game->img_door;
	if (wall_dir == 1)
		return &game->img_north;
	else if (wall_dir == 2)
		return &game->img_east;
	else if (wall_dir == 3)
		return &game->img_west;
	else if (wall_dir == 4)
		return &game->img_south;
	else
		return &game->img_north;
}

float calculate_wall_hit_x(t_game *game, int ray_index, float distance)
{
    float ray_angle = game->map->angle - FOV / 2 + (ray_index * FOV / WIDTH_3D);
    float hit_x, hit_y;
    
    hit_x = game->player_pixl_x + distance * cosf(ray_angle);
    hit_y = game->player_pixl_y + distance * sinf(ray_angle);

    int wall_dir = game->map->wall_direction[ray_index];
    if (wall_dir == 1 || wall_dir == 4)
        return hit_x - floor(hit_x / SIZE) * SIZE;
    else
        return hit_y - floor(hit_y / SIZE) * SIZE;
}


void draw_line_height(t_game *game, int x)
{
	int draw_start;
	float tex_step;
	float tex_pos;
	int draw_end;
    int y = 0;
    t_tex *tex = get_wall_texture(game, x);
    
    float wall_hit = calculate_wall_hit_x(game, x, game->map->dis[x]);
    int tex_x = (int)((wall_hit / SIZE) * tex->width);
    
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
    {
        tex_pos = (0 - game->wall_top) * tex_step;
    }
    
    while (y < HEIGHT_3D)
    {
        if (y < draw_start)
            put_pixel(game, x, y, 0xFF0000);
        else if (y <= draw_end)
        {
			// if(game->ray_valeu[x] == '1')
			// {
				// printf("game->ray_valeu[x]== %c\n",game->ray_valeu[x]);
            	int tex_y = (int)tex_pos;
	
            	if (tex_y >= tex->height)
					tex_y = tex->height - 1;
            	if (tex_y < 0)
					tex_y = 0;
	
            	int color = get_tex_pixel(tex, tex_x, tex_y);
            	put_pixel(game, x, y, color);
	
            	tex_pos += tex_step;
			// }
			// else
			// {
			// 	// int color = get_tex_pixel(tex, tex_x, tex_y);
            // 	// put_pixel(game, x, y, 0xFF0000);
			// 	// printf("game->ray_valeu[x]== %c \n",game->ray_valeu[x]);
			// }
        }
        else
            put_pixel(game, x, y, 0x8B4513);
        y++;
    }
}



void image_3d(t_game *game)
{
    int x = 0;
    game->distance_plane = (WIDTH_3D / 2) / tanf(FOV / 2);
    
    while (x < WIDTH_3D)
    {
        float ray_angle = game->map->angle - FOV / 2 + (x * FOV / WIDTH_3D);
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
	image_3d(game);
}

void	setup1_ray(t_game *game)
{
    float	new_x;
	float	new_y;
	float	cpy_angle;
    float	i;
	int		face;
	float	angle_step;

	angle_step = FOV / WIDTH_3D;
	cpy_angle = game->map->angle - FOV / 2;
	while (cpy_angle <= game->map->angle + FOV / 2)
	{
		i = 1;
		new_x = game->player_pixl_x + (cosf(cpy_angle) * i);
		new_y = game->player_pixl_y + (sinf(cpy_angle) * i);
		while (1)
		{
			new_x = game->player_pixl_x + (cosf(cpy_angle) * i);
			if (game->map->grid[((int)new_y) / SIZE][((int)new_x) / SIZE] == '1'
			 || game->map->grid[((int)new_y) / SIZE][((int)new_x) / SIZE] == 'D')
				break ;
			new_y = game->player_pixl_y + (sinf(cpy_angle) * i);
			if (game->map->grid[((int)new_y) / SIZE][((int)new_x) / SIZE] == '1'
				|| game->map->grid[((int)new_y) / SIZE][((int)new_x) / SIZE] == 'D')
				break ;
			put_pixel(game, (int)new_x / game->map->scale, (int)new_y / game->map->scale, 0x00FFFF00);
			i++;
		}
		cpy_angle += angle_step;
	}
}
