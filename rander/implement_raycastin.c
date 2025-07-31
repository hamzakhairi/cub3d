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


void Move_game(t_game *game, int y, int x, int key)
{
	int new_x;
	int new_y;
	int a_y;
	int b_x;
	int c_y;
	int d_x;
	int t_y;
	int r_x;
	int m_y;
	int n_x;

	a_y = (y - 12) / SIZE;
	b_x = (x - 12) / SIZE;
	c_y = (y + 12) / SIZE;
	d_x = (x - 12) / SIZE;
	t_y = (y - 12) / SIZE;
	r_x = (x + 12) / SIZE;
	m_y = (y + 12) / SIZE;
	n_x = (x + 12) / SIZE;
	printf("a_y = %d\n",a_y);
	printf("b_x = %d\n",b_x);
	printf("c_y = %d\n",c_y);
	printf("d_x = %d\n",d_x);
	printf("t_y = %d\n",t_y);
	printf("r_x = %d\n",r_x);
	printf("m_y = %d\n",m_y);
	printf("n_x = %d\n",n_x);
	if (game->map->grid[a_y][b_x] != '1' && game->map->grid[c_y][d_x] != '1'
		&& game->map->grid[t_y][r_x] != '1' && game->map->grid[m_y][n_x] != '1')
	{
		game->player_pixl_y = y;
		game->player_pixl_x = x;
	}
}

int	moving(int key, t_game *game)
{
	float new_x;
	float new_y;
	printf("key = %d\n", key);
	if (key == ESC)
		exit(0);
	else if (key == KEY_S)
	{
		new_x = game->player_pixl_x + (sinf(game->map->angle) * -NUM_GAME_MOVES);
		new_y = game->player_pixl_y + (cosf(game->map->angle) * NUM_GAME_MOVES);
		Move_game(game, new_y, new_x, key);
		printf("x = %f\n",(sinf(game->map->angle) * -NUM_GAME_MOVES));
		printf("y = %f\n",(cosf(game->map->angle) * NUM_GAME_MOVES));
	}
	else if (key == KEY_W)
	{
		new_x = game->player_pixl_x + (sinf(game->map->angle) * NUM_GAME_MOVES);
		new_y = game->player_pixl_y + (cosf(game->map->angle) * -NUM_GAME_MOVES);
		Move_game(game, new_y, new_x, key);
		printf("x = %f\n",(sinf(game->map->angle) * NUM_GAME_MOVES));
		printf("y = %f\n",(cosf(game->map->angle) * -NUM_GAME_MOVES));
	}
	else if (key == KEY_A)
	{
		new_x = game->player_pixl_x + (cosf(game->map->angle) * -NUM_GAME_MOVES);
		new_y = game->player_pixl_y + (sinf(game->map->angle) * -NUM_GAME_MOVES);
		Move_game(game, new_y, new_x, key);
		printf("x = %f\n",(cosf(game->map->angle) * -NUM_GAME_MOVES));
		printf("y = %f\n",(sinf(game->map->angle) * -NUM_GAME_MOVES));
	}
	else if (key == KEY_D)
	{
		new_x = game->player_pixl_x + (cosf(game->map->angle) * NUM_GAME_MOVES);
		new_y = game->player_pixl_y + (sinf(game->map->angle) * NUM_GAME_MOVES);
		Move_game(game, new_y, new_x, key);
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