#include "../cub.h"

void    setup_player(t_game *game)
{
    int    i;
    int    j;

    int    r = 8;
    int    center_x = game->player_pixl_x;
    int    center_y = game->player_pixl_y;

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

void image_3D(t_game *game)
{
	int y = 0;
	int x = 0;
	float distance_plane;
	float wall_height;
	int wall_top;
	int wall_bottom;
	float cpy_angle;
	float corrected_distance;

	distance_plane = (WIDTH_3D / 2) / tanf(FOV / 2);
	cpy_angle = game->map->angle - FOV / 2;
	x = 0;
	while(x < WIDTH_3D)
	{
		// Fix fisheye effect by using perpendicular distance
		corrected_distance = game->map->dis[x] * cosf(game->map->angle - (game->map->angle - FOV / 2 + (x * FOV / WIDTH_3D)));
		wall_height = (SIZE / corrected_distance) * distance_plane;
		wall_top = (HEIGHT_3D / 2) - (wall_height / 2);
		wall_bottom = (HEIGHT_3D / 2) + (wall_height / 2);
		
		if (wall_top < 0)
			wall_top = 0;
		if (wall_bottom >= HEIGHT_3D)
			wall_bottom = HEIGHT_3D - 1;
		
		y = 0;
		while (y < HEIGHT_3D)
		{
			if (y < wall_top)
				put_pixel(game, x, y, 0xFF0000);
			else if (y < wall_top + wall_height)
			{
				if (game->map->wall_direction[x] == 1)
					put_pixel(game, x, y, 0x000000);//Black
				else if (game->map->wall_direction[x] == 2)
					put_pixel(game, x, y, 0xFFFFFF);//White
				else if ((int)game->map->wall_direction[x] == 3)
					put_pixel(game, x, y, 0x0000FF);//Blue
				else if ((int)game->map->wall_direction[x] == 4)
					put_pixel(game, x, y, 0x00FF00);//green
			}
			else
				put_pixel(game, x, y, 0x8B4513);
			y++;
		}
		x++;
	}
}

void setup_ray(t_game *game)
{

    float ray_angle;
	float angle_step;
	int ray_count;

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
	image_3D(game);
}


void setup1_ray(t_game *game)
{
    float new_x;
	float new_y;
	float cpy_angle;
    float i;
	int face;
	float angle_step = FOV / WIDTH_3D;
	cpy_angle = game->map->angle - FOV / 2;
	while(cpy_angle <= game->map->angle + FOV / 2)
	{
		i = 1;
		new_x = game->player_pixl_x / 4 + (cosf(cpy_angle) * i);
		new_y = game->player_pixl_y / 4 + (sinf(cpy_angle) * i);
		while(1)
		{
			new_x = game->player_pixl_x / 4 + (cosf(cpy_angle) * i);
			if (game->map->grid[((int)new_y * 4) / SIZE][((int)new_x * 4) / SIZE] == '1')
				break ;
			new_y = game->player_pixl_y / 4  + (sinf(cpy_angle) * i);
			if (game->map->grid[((int)new_y * 4) /SIZE][((int)new_x * 4) / SIZE] == '1')
				break ;
			put_pixel(game, (int)new_x, (int)new_y, 0x00FFFF00);
			i++;
		}
		cpy_angle += angle_step;
	}
}



