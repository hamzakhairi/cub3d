#include "../cub.h"

void Calculate_width_height(t_game *game)
{
	int width;
	int height;

	height = 0;
	game->player_pixl_x = game->player_x * SIZE + (SIZE / 2);
	game->player_pixl_y = game->player_y * SIZE + (SIZE / 2);
	while (game->map->grid[height])
	{
		width = 0;
		while (game->map->grid[height][width])
		{
			if (game->map->grid[height][width] == 'N' || game->map->grid[height][width] == 'S'
				|| game->map->grid[height][width] == 'E' || game->map->grid[height][width] == 'W')
				store_dir(game, width, height);
			width++;
		}
		height++;
	}
	game->map->width = width * SIZE;
	game->map->height = height * SIZE;
}

void    put_pixel(t_game *game, int x, int y, int color)
{
    char    *dst;

    dst = game->addr + (y * game->line_length + x * game->bits_per_pixel / 8);
    *(unsigned int*)dst = color;
}

void ft_image(t_game *game, int width, int height)
{
	int y;
	int x;
	int color;
	y = 0;
	if (game->map->grid[height][width] == '1')
		color = 0x0000FF;
	else
		color = 0;
	while(y < 32)
	{
		x = 0;
		while (x < 32)
		{
			put_pixel(game, x + width * SIZE, y + height * SIZE, color);
			x++;
		}
		y++;
	}
}

void store_dir(t_game *game, int width, int height)
{
	if (game->map->grid[height][width] == 'N')
		game->map->angle = 0; // 0 degrees
	else if (game->map->grid[height][width] == 'S')
		game->map->angle = 3.1415926536; // 180 degrees
	else if (game->map->grid[height][width] == 'E')
		game->map->angle = 1.5707963268; // 90 degrees
	else if (game->map->grid[height][width] == 'W')
		game->map->angle = 4.7123889804; // 270 degrees
}

void create_put_image_to_window(t_game *game)
{
	int width;
	int height;
	int y;
	int x;

	height = 0;
	width = 0;
	while (game->map->grid[height])
	{
        width = 0;
		while (game->map->grid[height][width])
		{
            ft_image(game, width, height);
			width++; 
		}
		height++;
	}
	setup_player(game);
	setup_ray(game);
}

int create_xpm_file_image(t_game *game)
{
	int x;
	int y;

	game->img_ptr = mlx_new_image(game->mlx_ptr, game->map->width, game->map->height);
	if (!game->img_ptr)
		return (1);
	game->addr = mlx_get_data_addr(game->img_ptr, &game->bits_per_pixel, &game->line_length, &game->endian);
	create_put_image_to_window(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img_ptr, 0, 0);
	return (0);
}
