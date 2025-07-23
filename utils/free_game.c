
#include "../cub.h"

void free_config(t_config *config)
{
    if (config->no_texture)
        free(config->no_texture);
    if (config->so_texture)
        free(config->so_texture);
    if (config->we_texture)
        free(config->we_texture);
    if (config->ea_texture)
        free(config->ea_texture);
    if (config->check_duplicate)
        free(config->check_duplicate);
    free(config);
}

void free_map(t_map *map)
{
    int i = 0;
    while (map->grid[i])
    {
        free(map->grid[i]);
        i++;
    }
    free(map->grid);
}

void	free_images(t_game	*game)
{
	if (game->img_no)
		mlx_destroy_image(game->mlx_ptr, game->img_no);
	if (game->img_so)
		mlx_destroy_image(game->mlx_ptr, game->img_so);
	if (game->img_we)
		mlx_destroy_image(game->mlx_ptr, game->img_we);
	if (game->img_wa)
		mlx_destroy_image(game->mlx_ptr, game->img_wa);
}

void free_game(t_game *game)
{
    if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
    free_images(game);
    free_map(game->map);
    free_config(game->config);
    free(game->map);
    free(game);
}