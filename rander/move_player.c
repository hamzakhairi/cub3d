#include "../cub.h"

int player_rotation(t_game *game)
{
	if (game->map->key == KEY_LEFT)
		game->map->angle = game->map->angle - 0.1;
	else if (game->map->key == KEY_RIGHT)
		game->map->angle = game->map->angle + 0.1;
	if (game->map->angle >= 2 * M_PI)
		game->map->angle -= 2 * M_PI;
	if (game->map->angle < 0)
		game->map->angle += 2 * M_PI;
	return (0);
}

int Move_player(t_game *game, float y, float x, int i)
{
	float move_player_size_x_y;

	float a_y;
	float b_x;
	float c_y;
	float d_x;
	float t_y;
	float r_x;
	float m_y;
	float n_x;

	float a_yy;
	float b_xx;
	float c_yy;
	float d_xx;
	float t_yy;
	float r_xx;
	float m_yy;
	float n_xx;

	move_player_size_x_y = sqrtf(powf(MOVE_PLAYER_SIZE, 2) - (powf(MOVE_PLAYER_SIZE, 2) / 2));

	a_y = (y - MOVE_PLAYER_SIZE) / SIZE;
	b_x = (x) / SIZE;
	c_y = (y + MOVE_PLAYER_SIZE) / SIZE;
	d_x = (x) / SIZE;
	t_y = (y) / SIZE;
	r_x = (x + MOVE_PLAYER_SIZE) / SIZE;

	m_y = (y) / SIZE;
	n_x = (x - MOVE_PLAYER_SIZE) / SIZE;
//
	a_yy = (y - move_player_size_x_y) / SIZE;
	b_xx =(x + move_player_size_x_y) / SIZE;

	c_yy = (y + move_player_size_x_y) / SIZE;
	d_xx =(x + move_player_size_x_y) / SIZE;

	t_yy = (y - move_player_size_x_y) / SIZE;
	r_xx =(x - move_player_size_x_y) / SIZE;

	m_yy = (y + move_player_size_x_y) / SIZE;
	n_xx =(x - move_player_size_x_y) / SIZE;

	if (game->map->grid[(int)a_y][(int)b_x] != '1' && game->map->grid[(int)c_y][(int)d_x] != '1' 
		&& game->map->grid[(int)t_y][(int)r_x] != '1' && game->map->grid[(int)m_y][(int)n_x] != '1'
		&& game->map->grid[(int)a_yy][(int)b_xx] != '1' && game->map->grid[(int)c_yy][(int)d_xx] != '1'
		&& game->map->grid[(int)t_yy][(int)r_xx] != '1' && game->map->grid[(int)m_yy][(int)n_xx] != '1'
		&& (game->map->grid[(int)y / SIZE][(int)x / SIZE] != 'D' || game->is_open_door))
	{
		game->player_pixl_x = x;
		game->player_pixl_y = y;
		return (0);
	}
	return (1);
}

int move_game(t_game *game, int i)
{
	float new_x;
	float new_y;
	int check;

	if (game->map->key == KEY_S)
	{
		new_x = game->player_pixl_x - (cosf(game->map->angle) * i);
		new_y = game->player_pixl_y - (sinf(game->map->angle) * i);
		check = Move_player(game, new_y, new_x, i);
	}
	else if (game->map->key == KEY_W)
	{
		new_x = game->player_pixl_x + (cosf(game->map->angle) * i);
		new_y = game->player_pixl_y + (sinf(game->map->angle) * i);
		check = Move_player(game, new_y, new_x , i);
	}
	else if (game->map->key == KEY_A)
	{
		new_x = game->player_pixl_x - (sinf(game->map->angle) * i);
		new_y = game->player_pixl_y + (cosf(game->map->angle) * i);
		check = Move_player(game, new_y, new_x, i);
	}
	else if (game->map->key == KEY_D)
	{
		new_x = game->player_pixl_x + (sinf(game->map->angle) * i);
		new_y = game->player_pixl_y - (cosf(game->map->angle) * i);
		check = Move_player(game, new_y, new_x, i);
	}
	return (check);
}


int	moving(int key, t_game *game)
{
	game->map->key = key;
	int i;
	int check;
	float new_x;
	float new_y;


	i = NUM_GAME_MOVES;
	while(i > 0)
	{
		if (game->map->key == ESC)
			exit(0);
		else if (game->map->key == KEY_S || game->map->key == KEY_W || game->map->key == KEY_A || game->map->key == KEY_D)
		{
			check = move_game(game, i);
		}
		else if (game->map->key == KEY_T)
		{
			game->img_player->is_state = 1;
			game->img_player->current_image = 0;
			check = 0;
		}
		else if (game->map->key == KEY_Q)
		{
			if (!game->is_open_door)
				game->is_open_door = 1;
			else
				game->is_open_door = 0;
			check = 0;
		}
		else if (game->map->key == KEY_F)
		{
			game->img_player->is_state = 2;
			game->img_player->current_image = 0;
			check = 0;
		}
		else if (game->map->key == KEY_LEFT || game->map->key == KEY_RIGHT)
			check = player_rotation(game);
		else if (game->map->key == KEY_ZOOM)
		{
			if(game->map->iszoom == 0)
			{
				game->map->player_size = 8;
				game->map->minimap_size = 250;
				game->map->prefix_palyer_x = WIDTH_3D / 2;
				game->map->prefix_palyer_y = HEIGHT_3D / 2;
				game->map->scale = 1;
				game->map->iszoom = 1;
			}
			else
			{
				game->map->player_size = PLAYER_SIZE;
				game->map->minimap_size = 100;
				game->map->prefix_palyer_x = 102;
				game->map->prefix_palyer_y = 102;
				game->map->scale = SCALE;
				game->map->iszoom = 0;
			}
			check = 0;
		}
		if (check == 0)
			break ;
		i--;
	}
	return (0);
}
