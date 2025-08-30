#include "../cub.h"

int player_rotation(t_game *game)
{
	if (game->map->key == KEY_LEFT)
		game->map->angle = game->map->angle - 0.1;
	else if (game->map->key == KEY_RIGHT)
		game->map->angle = game->map->angle + 0.1;
	if(game->map->angle >= 2 * M_PI)
		game->map->angle -= 2 * M_PI;
	if (game->map->angle < 0)
		game->map->angle += 2 * M_PI;
	return (0);
}

int Move_player(t_game *game, float y, float x, int i)
{
	if (game->map->RayFacingUp && game->map->RayFacingLeft)
		y = y - 1;
	else if (game->map->RayFacingRight && game->map->RayFacingDown)
		x = x - 1;
	else if (game->map->RayFacingUp && game->map->RayFacingRight)
	{
		x = x - 1;
		y = y - 1;
	}

	if (game->map->grid[(int)y / SIZE][(int)x / SIZE] != '1')
	{
		game->player_pixl_y = y;
		game->player_pixl_x = x;
		return(0);
	}
	return (1);
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
		else if (game->map->key == KEY_S)
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
		else if (game->map->key == KEY_T)
		{
			game->img_player->isWhat_shot_walk = 1;
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
				game->map->player_size = 4;
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
