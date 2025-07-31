#include "../cub.h"

int create_window(t_game *game)
{
	Calculate_width_height(game);
	printf("======{%f}\n",game->map->angle);
	game->mlx_ptr = mlx_init();
    if (!game->mlx_ptr)
        return (1);
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->map->width, game->map->height, "cub3D");
    if (!game->win_ptr)
        return (1);
	if (create_xpm_file_image(game))
		return (1);
	create_put_image_to_window(game);
	mlx_hook(game->win_ptr, 2, 1L<<0, moving, game);
	return (0);
}

int	start_randering(t_game *game)
{
	if (create_window(game))
		return (1);
	mlx_loop(game->mlx_ptr);
	return (0);
}
