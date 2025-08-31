
# include "../cub.h"

int get_map_length(char *path, int skip_lines)
{
    char *line = NULL;
    int length = 0;
    int i = 0;
    int fd = open(path, O_RDONLY, 0644);
    if (fd < 0)
        return (ft_putendl_fd(NOT_FOUND, 2), -1);
    while (i < skip_lines - 1 && (line = get_next_line(fd)))
    {
        free(line);
        i++;
    }

    while ((line = get_next_line(fd)))
    {
        length++;
        free(line);
    }
    close(fd);
    return length;
}

int filling_map(t_game *game, char *path)
{
    int fd = open(path, O_RDONLY, 0644);
    if (fd < 0)
        return (ft_putendl_fd(NOT_FOUND, 2), 0);
    int lenght = get_map_length(path, game->start_parcing_map);
    if (lenght == -1)
        return (0);
    game->map->grid = malloc(sizeof(char *) * (lenght + 1));
    if (!game->map->grid)
        return (close(fd), ft_putendl_fd(ERROR_ALOCATION, 2), 0);
    int i = 0;
    char *line = NULL;
    while (i < game->start_parcing_map - 1)
    {
        line = get_next_line(fd);
        if(!line)
            break;
        free(line);
        i++;
    }
    i = 0;
    line = get_next_line(fd);
    while (line)
    {
        game->map->grid[i] = ft_other_strdup(line);
        if (!game->map->grid[i])
        {
            free(line);
            game->map->grid[i] = NULL;
            return(printf("{}{}{}{}{1}{1}\n"),ft_putendl_fd(ERROR_MAP, 2), 0);
        }
        free(line);
        i++;
        line = get_next_line(fd);
    }
    game->map->grid[i] = NULL;
    close(fd);
    return (1);
}

