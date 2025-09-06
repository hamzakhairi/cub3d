#include "../cub.h"

void	get_horizontal(t_game *game)
{
	float	yh_step;
	float	xh_step;

	yh_step = SIZE;
	if (game->map->RayFacingUp)
		yh_step *= -1;
	xh_step = SIZE / tanf(game->map->angle);
	if (game->map->RayFacingLeft && xh_step > 0)
		xh_step *= -1;
	if (game->map->RayFacingRight && xh_step < 0)
		xh_step *= -1;
	game->map->Y_horizontal += yh_step;
	game->map->X_horizontal += xh_step;
}

float	horizontal_door(t_game *game, int check_y, int xh, int yh)
{
	if (check_y >= 0 && check_y < (game->map->height / SIZE)
		&& xh < (int)strlen(game->map->grid[check_y])
		&& game->map->grid[check_y] != NULL
		&& (game->map->grid[check_y][xh] == '1'
		|| (game->map->grid[check_y][xh] == 'D' && !game->is_open_door)))
	{
		if (game->map->grid[check_y][xh] == '1')
			game->ray_valeu_h = '1';
		else
		{
			game->is_door_hy = check_y;
			game->is_door_hx = xh;
			game->ray_valeu_h = 'D';
			game->dst_door_h = sqrtf(powf(game->map->X_horizontal \
			- game->player_pixl_x, 2) \
			+ powf(game->map->Y_horizontal - game->player_pixl_y, 2));
		}
		return (sqrtf(powf(game->map->X_horizontal - game->player_pixl_x, 2) \
		+ powf(game->map->Y_horizontal - game->player_pixl_y, 2)));
	}
	return (-1);
}

float	horizontal_wall(t_game *game)
{
	int		xh;
	int		yh;
	int		check_y;
	float	dst;

	while (1)
	{
		xh = (int)game->map->X_horizontal / SIZE;
		yh = (int)game->map->Y_horizontal / SIZE;
		if (xh < 0 || yh < 0 || xh >= (game->map->width / SIZE)
			|| yh >= (game->map->height / SIZE)
			|| game->map->grid[yh] == NULL
			|| xh >= (int)strlen(game->map->grid[yh]))
			break ;
		check_y = yh;
		if (game->map->RayFacingUp)
			check_y = yh - 1;
		dst = horizontal_door(game, check_y, xh, yh);
		if (dst != -1)
			return (dst);
		get_horizontal(game);
	}
	return (INFINITY);
}