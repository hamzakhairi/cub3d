#include "../cub.h"


 
void get_horizontal(t_game *game, float horizontal)
{
	game->map->Xh_horizontal = (horizontal - game->player_pixl_y) / tanf(game->map->angle) + game->player_pixl_x;
	game->map->Yh_horizontal = horizontal;

}

// void get_vertical(t_game *game, float vertical)
// {
// 	game->map->Xh_vertical = vertical;
// 	game->map->Yh_vertical = (vertical - game->player_pixl_x) * tanf(game->map->angle) + game->player_pixl_y;
// }

// void check_ray(t_game *game)
// {
// 	int x;
// 	int y;
// 	float vertical = floorf(game->player_pixl_x / SIZE) * SIZE;
// 	float horizontal = floorf(game->player_pixl_y / SIZE) * SIZE;
// 	while (1)
// 	{
// 		get_vertical(game, vertical);
// 		get_horizontal(game, horizontal);
// 		x = (int)game->map->Xh_horizontal / SIZE;
// 		y = (int)game->map->Yh_horizontal / SIZE;
// 		printf("x = %f             y = %f\n",game->map->Xh_vertical,game->map->Yh_vertical);
// 		if (game->map->grid[y][x] == '1')
// 		{

// 			game->map->d_X = game->map->Xh_horizontal;
// 			game->map->d_Y = game->map->Yh_horizontal;
// 			break ;
// 		}
// 		printf("youddfr\n");
// 		vertical += SIZE;
// 		horizontal += SIZE;
// 	}
// }

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
	int new_x;
	int new_y;
	float distance_palne;
	float wall_top_pixel;
	float wall_bottom_pixel;
	float wall_strip;

	distance_palne = ((float)game->map->width / 2) / tanf(FOV / 2);
	// printf("distance_palne = %f\n", distance_palne);
	while (x < game->map->width)
	{
		wall_strip = (SIZE / game->map->dis[x]) * distance_palne;
		wall_top_pixel = ((float)game->map->height / 2) - (wall_strip / 2);
		wall_bottom_pixel = ((float)game->map->height / 2) + (wall_strip / 2);
		y = 0;
		while (y < game->map->height)
		{
			new_x = x;
			new_y = y;
			if (y < wall_top_pixel)
				put_pixel(game, new_x, new_y, 0x0000FF);
			else if (y < wall_strip + wall_top_pixel )
			{
				put_pixel(game, new_x, new_y, 0x00FFFF00);
			}
			else
				put_pixel(game, new_x, new_y, 0);
			y++;
		}
		x++;
	}
}

void setup_ray(t_game *game)
{
    float new_x;
	float new_y;
	float cpy_angle;
    float i;
	// int	n = 1;
	game->map->width_angel = 0;
//    check_ray(game);
	cpy_angle = game->map->angle - FOV / 2;
	while(cpy_angle <= game->map->angle + FOV / 2)
	{
		i = 1;
		new_x = game->player_pixl_x + (cosf(cpy_angle) * i);
		new_y = game->player_pixl_y + (sinf(cpy_angle) * i);
		// if (game->map->grid[(int)new_y / SIZE][(int)new_x / SIZE] == '1')
		// 	n = 0;
		while(1)
		{
			new_x = game->player_pixl_x + (cosf(cpy_angle) * i);
			if (game->map->grid[(int)new_y / SIZE][(int)new_x / SIZE] == '1')
				break ;
			new_y = game->player_pixl_y + (sinf(cpy_angle) * i);
			if (game->map->grid[(int)new_y / SIZE][(int)new_x / SIZE] == '1')
				break ;
			put_pixel(game, new_x, new_y, 0x00FFFF00);
			i++;
		}
		game->map->dis[game->map->width_angel] = sqrtf(powf(new_x - game->player_pixl_x, 2) + powf(new_y - game->player_pixl_y, 2));
		game->map->width_angel++;
		cpy_angle += 0.001;
	}

}
