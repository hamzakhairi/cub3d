#include "../cub.h"

void put_pixel(t_game *game, int x, int y, int color)
{
    if (x < 0 || y < 0 || x >= WIDTH_3D || y >= HEIGHT_3D)
        return;
    char *dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void ft_image_minimap(t_game *game, int width, int height)
{
	int y;
	int x;
	int color;
	int scale = 4;
	int mini_size = SIZE / scale;
	
	y = 0;
	if (game->map->grid[height][width] == '1')
		color = 0x0000FF;
	else
		color = 0x000000;
		
	while(y < mini_size)
	{
		x = 0;
		while (x < mini_size)
		{
			put_pixel(game, x + width * mini_size, y + height * mini_size, color);
			x++;
		}
		y++;
	}
}


void setup_minimap_player(t_game *game)
{
    int i, j;
    int r = 2;
    int scale = 4;
    int center_x = (game->player_pixl_x / scale);
    int center_y = (game->player_pixl_y / scale);

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

void create_put_image_to_window(t_game *game)
{
	int width;
	int height;

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

int create_image(t_game *game)
{
	game->img_ptr = mlx_new_image(game->mlx_ptr, WIDTH_3D, HEIGHT_3D);
	if (!game->img_ptr)
		return (1);
	game->addr = mlx_get_data_addr(game->img_ptr, &game->bits_per_pixel, &game->line_length, &game->endian);
	create_put_image_to_window(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img_ptr, 0, 0);
	return (0);
}
    