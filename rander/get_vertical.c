#include "../cub.h"

void	get_vertical(t_game *game)
{
	float	yv_step;
	float	xv_step;

	xv_step = SIZE;
	if (game->map->RayFacingLeft)
		xv_step *= -1;
	yv_step = SIZE * tanf(game->map->angle);
	if (game->map->RayFacingUp && yv_step > 0)
		yv_step *= -1;
	if (game->map->RayFacingDown && yv_step < 0)
		yv_step *= -1;
	game->map->X_vertical += xv_step;
	game->map->Y_vertical += yv_step;
}

float	vertical_door(t_game *game, int check_x, int xv, int yv)
{
	if (check_x >= 0 && check_x < (game->map->width / SIZE)
		&& yv < (game->map->height / SIZE)
		&& check_x < (int)strlen(game->map->grid[yv])
		&& (game->map->grid[yv][check_x] == '1'
		|| (game->map->grid[yv][check_x] == 'D' && !game->is_open_door)))
	{
		if (game->map->grid[yv][check_x] == '1')
			game->ray_valeu_v = '1';
		else
		{
			game->is_door_vy = yv;
			game->is_door_vx = check_x;
			game->dst_door_v = sqrtf(powf(game->map->X_vertical \
			- game->player_pixl_x, 2) \
			+ powf(game->map->Y_vertical - game->player_pixl_y, 2));
			game->ray_valeu_v = 'D';
		}
		return (sqrtf(powf(game->map->X_vertical - game->player_pixl_x, 2) \
		+ powf(game->map->Y_vertical - game->player_pixl_y, 2)));
	}
	return (-1);
}

float	vertical_wall(t_game *game)
{
	int		xv;
	int		yv;
	int		check_x;
	float	dst;

	while (1)
	{
		xv = (int)game->map->X_vertical / SIZE;
		yv = (int)game->map->Y_vertical / SIZE;
		if (xv < 0 || yv < 0 || xv >= (game->map->width / SIZE)
			|| yv >= (game->map->height / SIZE) || game->map->grid[yv] == NULL
			|| xv >= (int)strlen(game->map->grid[yv]))
			break ;
		check_x = xv;
		if (game->map->RayFacingLeft)
			check_x = xv - 1;
		dst = vertical_door(game, check_x, xv, yv);
		if (dst != -1)
			return (dst);
		get_vertical(game);
	}
	return (INFINITY);
}