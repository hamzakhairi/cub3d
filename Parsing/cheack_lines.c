
# include "../cub.h"

int ft_check_FL_line(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] != '1' && str[i] != ' ')
            return (0);
        i++;
    }
    return (1);
}

int check_dir(char *str, int index, t_game *game)
{
    int i = 0;
    int j = 0;
    int length = ft_strlen(str);

    
    while (str[i] == ' ' || str[i] == '\t')
    {
        i++;
    }
    while (str[i + j])
    {
        if (!ft_strchr(" 01NSWE", str[i + j]))
            return (ft_putendl_fd(ERROR_MAP, 2), 0);
        
        if ((j == 0 || ((j + i) == length - 1)) && (str[i + j] != '1'))
        {
            // printf("[%c]\n", str[i + j]);
            return (ft_putendl_fd(ERROR_MAP, 2), 0);
        }
        else
        {
            if (str[i + j] != '1')
            {
                // check left and right
                if ((str[i + j - 1] == ' ')
                    || (str[i + j + 1] && str[i + j + 1] == ' ')
                    || (!str[i + j + 1]))
                {
                    // printf("%s\n",str);
                    return (ft_putendl_fd(ERROR_MAP, 2), 0);
                }
                // check up
                else if (ft_strchr("0NSWE", str[i + j])
                    && game->map->grid[index - 1][i + j] == ' ')
                {
                    // printf("1: %s \n-[%c]-[%c]-[%d]\n",str,game->map->grid[index - 1][i + j], str[i + j], i+j);
                    return (ft_putendl_fd(ERROR_MAP, 2), 0);
                }
                // check down
                else if (ft_strchr("0NSWE", str[i + j])
                    && game->map->grid[index + 1][i + j] == ' ')
                {
                    // printf("2: %s\n",str);
                    return (ft_putendl_fd(ERROR_MAP, 2), 0);
                }
            }      
        }
        j++;
    }
    return (1);
}

int cheack_lines(t_game *game)
{
    int i;
    int j = 0;
    int count_player = 0;
    i = 0; 
    char **map = game->map->grid;
    while (map[i])
    {
        if (i == 0 || map[i + 1] == NULL)
        {
            if (!ft_check_FL_line(map[i]))
                return (ft_putendl_fd(ERROR_MAP, 2), 0);
        }
        else
        {
            if (!check_dir(map[i], i, game))
            {
                return (0);
            }
        }
        j = 0;
        while (map[i][j])
        {
            if (ft_strchr("NSWE", map[i][j]))
            {
                game->player_x = i;
                game->player_y = j;
                printf("[%c]\n", map[i][j]);
                count_player++;
                if (count_player != 1)
                    return (ft_putendl_fd(ERROR_MAP, 2), 0);
            }
            j++;
        }
        i++;
    }
    if (count_player == 0)
        return (ft_putendl_fd(ERROR_MAP, 2), 0);
    return (1);
}
