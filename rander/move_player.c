#include "../cub.h"

void player_rotation(t_game *game, int key)
{
	if (key == KEY_LEFT)
		game->map->angle = game->map->angle - 0.1;
	else if (key == KEY_RIGHT)
		game->map->angle = game->map->angle + 0.1;
	if(game->map->angle >= 2 * M_PI)
		game->map->angle -= 2 * M_PI;
	if (game->map->angle < 0)
		game->map->angle += 2 * M_PI;
}

void Move_player(t_game *game, float y, float x, int key)
{
	float a_y;
	float b_x;
	float c_y;
	float d_x;
	float t_y;
	float r_x;
	float m_y;
	float n_x;

	float b_xx;
	float c_yy;
	float t_yy;
	float n_xx;
	a_y = (y - 4) / SIZE;
	b_x = (x - 4) / SIZE;
	c_y = (y + 4) / SIZE;
	d_x = (x - 4) / SIZE;
	t_y = (y - 4) / SIZE;
	r_x = (x + 4) / SIZE;
	m_y = (y + 4) / SIZE;
	n_x = (x + 4) / SIZE;

	a_y = (y - 4) / SIZE;
	b_xx = (x) / SIZE;

	c_yy = (y) / SIZE;
	d_x = (x - 4) / SIZE;

	t_yy = (y) / SIZE;
	r_x = (x + 4) / SIZE;

	m_y = (y + 4) / SIZE;
	n_xx = (x) / SIZE;

		// &&game->map->grid[(int)a_y][(int)b_xx] != '1' && game->map->grid[(int)c_yy][(int)d_x] != '1'
		// && game->map->grid[(int)t_yy][(int)r_x] != '1' && game->map->grid[(int)m_y][(int)n_xx] != '1')

	printf("q==/ %c a===/ %c  s====/ %c r=====/ %c\n",game->map->grid[(int)a_y][(int)b_x],game->map->grid[(int)c_y][(int)d_x],game->map->grid[(int)t_y][(int)r_x],game->map->grid[(int)m_y][(int)n_x]);
	printf("/ %f/ %f/ %f/ %f/ %f/ %f/ %f/ %f\n", a_y,b_x,c_y,d_x,t_y,r_x,m_y,n_x);
	printf("y === %f  x == %f\n",y /32 ,x/32);
	if (game->map->grid[(int)a_y][(int)b_x] != '1' && game->map->grid[(int)c_y][(int)d_x] != '1'
		&& game->map->grid[(int)t_y][(int)r_x] != '1' && game->map->grid[(int)m_y][(int)n_x] != '1'
		&&game->map->grid[(int)a_y][(int)b_xx] != '1' && game->map->grid[(int)c_yy][(int)d_x] != '1'
		&& game->map->grid[(int)t_yy][(int)r_x] != '1' && game->map->grid[(int)m_y][(int)n_xx] != '1')
	{
		// printf("q== %c a=== %c  s==== %c r===== %c\n",game->map->grid[a_y][b_x],game->map->grid[c_y][d_x],game->map->grid[t_y][r_x],game->map->grid[m_y][n_x]);
		game->player_pixl_y = y;
		game->player_pixl_x = x;
	}
	// a_y = y/ SIZE;
	// b_x = (x - 4) / SIZE;
	// c_y = y/ SIZE;
	// d_x = (x - 4) / SIZE;
	// t_y = y/ SIZE;
	// r_x = (x + 4) / SIZE;
	// m_y = y/ SIZE;
	// n_x = (x + 4) / SIZE;

	else if (game->map->grid[(int)y/ SIZE][(int)(x - 4) / SIZE] != '1' && game->map->grid[(int)y/ SIZE][(int)(x - 4) / SIZE] != '1'
		&& game->map->grid[(int)y/ SIZE][(int)(x + 4) / SIZE] != '1' && game->map->grid[(int)y/ SIZE][(int)(x + 4) / SIZE] != '1' && (key == KEY_W || key == KEY_S))
	{
		game->player_pixl_x = x;
	}
	// a_y = (y - 4) / SIZE;
	// b_x = x / SIZE;
	// c_y = (y + 4) / SIZE;
	// d_x = x / SIZE;
	// t_y = (y - 4) / SIZE;
	// r_x = x / SIZE;
	// m_y = (y + 4) / SIZE;
	// n_x = x / SIZE;
	else if (game->map->grid[(int)(y - 4) / SIZE][(int) x / SIZE] != '1' && game->map->grid[(int)(y + 4) / SIZE][(int)x / SIZE] != '1'
		&& game->map->grid[(int)(y - 4) / SIZE][(int)x / SIZE] != '1' && game->map->grid[(int)(y + 4) / SIZE][(int)x / SIZE] != '1' && (key == KEY_W || key == KEY_S))
	{
		game->player_pixl_y = y;
	}
}

int	moving(int key, t_game *game)
{
	float new_x;
	float new_y;
	
	if (key == ESC)
		exit(0);
	else if (key == KEY_S)
	{
		new_x = game->player_pixl_x - (cosf(game->map->angle) * NUM_GAME_MOVES);
		new_y = game->player_pixl_y - (sinf(game->map->angle) * NUM_GAME_MOVES);
		Move_player(game, new_y, new_x, key);
	}
	else if (key == KEY_W)
	{
		new_x = game->player_pixl_x + (cosf(game->map->angle) * NUM_GAME_MOVES);
		new_y = game->player_pixl_y + (sinf(game->map->angle) * NUM_GAME_MOVES);
		Move_player(game, new_y, new_x, key);
	}
	else if (key == KEY_A)
	{
		new_x = game->player_pixl_x - (sinf(game->map->angle) * NUM_GAME_MOVES);
		new_y = game->player_pixl_y + (cosf(game->map->angle) * NUM_GAME_MOVES);
		Move_player(game, new_y, new_x, key);
	}
	else if (key == KEY_D)
	{
		new_x = game->player_pixl_x + (sinf(game->map->angle) * NUM_GAME_MOVES);
		new_y = game->player_pixl_y - (cosf(game->map->angle) * NUM_GAME_MOVES);
		Move_player(game, new_y, new_x, key);
	}
	else if (key == KEY_LEFT || key == KEY_RIGHT)
		player_rotation(game, key);
	
	create_put_image_to_window(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img_ptr, 0, 0);
	return (0);
}