
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
        // printf("free ::: %d\n", i);
        free(map->grid[i]);
        i++;
    }
    free(map->grid);
    free(map);
}

void free_game(t_game *game)
{
    if (game->map)
        free_map(game->map);
    if (game->config)
        free_config(game->config);
    if(game->mlx_ptr)
        free(game->mlx_ptr);
    if(game->win_ptr)
        free(game->win_ptr);
     if(game->img_ptr)
        free(game->img_ptr);
    free(game);
}
