/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_create_window.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:04:49 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/08/31 09:42:07 by hkhairi          ###   ########.fr       */
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

void setup_minimap_player(t_game *game)
{
    int i, j, color, r;
    int center_x, center_y;
    int map_x, map_y;
    int max_grid_x, max_grid_y;
    
    max_grid_y = 0;
    while (game->map->grid[max_grid_y] != NULL)
        max_grid_y++;
    
    max_grid_x = 0;
    if (max_grid_y > 0)
        max_grid_x = strlen(game->map->grid[0]);
    
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
                
                map_x = center_x / SIZE;
                map_y = center_y / SIZE;
            
                if (center_x < 0 || center_y < 0 || 
                    center_x >= game->map->width || center_y >= game->map->height ||
                    map_y < 0 || map_y >= max_grid_y ||
                    map_x < 0 || map_x >= max_grid_x ||
                    game->map->grid[map_y] == NULL ||
                    map_x >= (int)strlen(game->map->grid[map_y]))
                {
                    color = 0x000000; // Black for out of bounds
                }
                else if (game->map->grid[map_y][map_x] == '1')
                    color = 0x0000FF; // Blue for walls
                else if (game->map->grid[map_y][map_x] == 'D' && !game->is_open_door)
                    color = 0x00FF00;
                else if (game->map->grid[map_y][map_x] == '0')
                    color = 0xB2BEB5; // Gray for empty spaces
                put_pixel(game, game->map->prefix_palyer_x + j, game->map->prefix_palyer_y + i, color);
            }
            j++;
        }
        i++;
    }
    // Draw player dot
    r = game->map->player_size;
    center_x = game->map->prefix_palyer_x;
    center_y = game->map->prefix_palyer_y;
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
	setup_ray(game);
	setup_minimap_player(game);
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
	if (load_texture(game, &game->img_door, "texter/door/1.xpm"))
		return (1);
	create_put_image_to_window(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img_ptr, 0, 0);
	return (0);
}
