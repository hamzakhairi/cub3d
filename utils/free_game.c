
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

void free_game(t_game *game)
{
    free_map(game->map);
    free_config(game->config);
    free(game->map);
    free(game);
}