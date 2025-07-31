#include "../cub.h"


void    setup_player(t_game *game)
{
    int    i;
    int    j;

    int    r = 10;
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



void Move_game1(t_game *game, int key)
{
	if (key == KEY_LEFT)
	{
		game->map->angle = game->map->angle - 0.5;
	}
	else if (key == KEY_RIGHT)
	{
		game->map->angle = game->map->angle + 0.5;
	}
}


// void Move_game(t_game *game, int y, int x, int key)
// {
// 	int new_x;
// 	int new_y;
// 	int a;
// 	int b;
// 	int c;
// 	int d;
// 	if(key == KEY_A)
// 	{
// 		a = (y - 12) / SIZE;
// 		b = (x - 12) / SIZE;
// 		c = (y + 12) / SIZE;
// 		d = (x - 12) / SIZE;
// 	}
// 	else if(key == KEY_S)
// 	{
// 		a = (y + 12) / SIZE;
// 		b = (x - 12) / SIZE;
// 		c = (y + 12) / SIZE;
// 		d = (x + 12) / SIZE;
// 	}
// 	else if (key == KEY_W)
// 	{
// 		a = (y - 12) / SIZE;
// 		b = (x - 12) / SIZE;
// 		c = (y - 12) / SIZE;
// 		d = (x + 12) / SIZE;
// 	}
// 	else if (key == KEY_D)
// 	{
// 		a = (y - 12) / SIZE;
// 		b = (x + 12) / SIZE;
// 		c = (y + 12) / SIZE;
// 		d = (x + 12) / SIZE;
// 	}
// 	if(game->map->grid[a][b] != '1' && game->map->grid[c][d] != '1')
// 	{
// 		game->player_pixl_y = y;
// 		game->player_pixl_x = x;
// 	}
// }

int	moving(int key, t_game *game)
{

	printf("key = %d\n", key);
	if (key == ESC)
		exit(0);
	else if (key == KEY_S)
	{
		game->player_pixl_x = game->player_pixl_x + (sinf(game->map->angle) * -NUM_GAME_MOVES);
		game->player_pixl_y = game->player_pixl_y + (cosf(game->map->angle) * NUM_GAME_MOVES);
		printf("x = %f\n",(sinf(game->map->angle) * -NUM_GAME_MOVES));
		printf("y = %f\n",(cosf(game->map->angle) * NUM_GAME_MOVES));
	}
	else if (key == KEY_W)
	{
		game->player_pixl_x = game->player_pixl_x + (sinf(game->map->angle) * NUM_GAME_MOVES);
		game->player_pixl_y = game->player_pixl_y + (cosf(game->map->angle) * -NUM_GAME_MOVES);
		printf("x = %f\n",(sinf(game->map->angle) * NUM_GAME_MOVES));
		printf("y = %f\n",(cosf(game->map->angle) * -NUM_GAME_MOVES));
	}
	else if (key == KEY_A)
	{
		game->player_pixl_x = game->player_pixl_x + (cosf(game->map->angle) * -NUM_GAME_MOVES);
		game->player_pixl_y = game->player_pixl_y + (sinf(game->map->angle) * -NUM_GAME_MOVES);
		printf("x = %f\n",(cosf(game->map->angle) * -NUM_GAME_MOVES));
		printf("y = %f\n",(sinf(game->map->angle) * -NUM_GAME_MOVES));
	}
	else if (key == KEY_D)
	{
		game->player_pixl_x = game->player_pixl_x + (cosf(game->map->angle) * NUM_GAME_MOVES);
		game->player_pixl_y = game->player_pixl_y + (sinf(game->map->angle) * NUM_GAME_MOVES);
		printf("x = %f\n",(sinf(game->map->angle) * NUM_GAME_MOVES));
		printf("y = %f\n",(cosf(game->map->angle) * NUM_GAME_MOVES));
	}
	else if (key == KEY_LEFT || key == KEY_RIGHT)
	{
		Move_game1(game, key);
	}
	create_put_image_to_window(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img_ptr, 0, 0);
	return (0);
}