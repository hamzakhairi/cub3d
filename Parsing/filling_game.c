/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:12:05 by hkhairi           #+#    #+#             */
/*   Updated: 2025/08/30 17:03:32 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub.h"



int check_if_start_prcing_map(char *str)
{
    int i;

    i = 0;
    while (str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;
    if (str[i] && (str[i] == '1'))
        return (0);
    else if (str[i] && (str[i] == '0'))
        return (0);
    else if (str[i] && (str[i] == 'N'))
    {
        if (str[i + 1] && str[i + 1] != 'O')
        {
            return (0);
        }
    }
    else if (str[i] && (str[i] == 'S'))
    {
        if (str[i + 1] && str[i + 1] != 'O')
        {
            return (0);
        }
    }
    else if (str[i] && (str[i] == 'E'))
    {
        if (str[i + 1] && str[i + 1] != 'A')
        {
            return (0);
        }
    }
    else if (str[i] && (str[i] == 'W'))
    {
        if (str[i + 1] && str[i + 1] != 'E')
        {
            return (0);
        }
    }
    return (1);
}

int filling_game(int argc, char *argv[], t_game *game)
{
    (void)argc;
    int fd = open(argv[1], O_RDONLY, 0644);
    if (fd < 0)
        return (ft_putendl_fd(NOT_FOUND, 2), 0);
    char *str = get_next_line(fd);
    int start;

    start = 0;
    while (str)
    {
        if (game->start_parcing_map == -1 && !check_diection_texter(game, str))
            return (get_next_line(-1), free(str), 0);
        else if (game->start_parcing_map == -1 && !check_cloros(game, str))
            return (get_next_line(-1), free(str), 0);
        else if (!check_if_start_prcing_map(str))
        {
            game->start_parcing_map = ++start;
            get_next_line(-1);
            free(str);
            break;
        }
        start++;
            // printf("%s", str);
        // else if ()
        //     return (ft_putendl_fd(ERROR_KEY, 2),get_next_line(-1), free(str), 0);
        free(str);
        str = get_next_line(fd);
    }

    // printf("\n[%s]\n[%s]\n[%s]\n[%s]\n F : [%d,%d,%d]\n C : [%d,%d,%d]\nline : [%d]\n", game->config->no_texture, game->config->so_texture, game->config->we_texture
    // ,game->config->ea_texture
    // ,game->config->floor_color[0]
    // ,game->config->floor_color[1]
    // ,game->config->floor_color[2]
    // ,game->config->ceiling_color[0]
    // ,game->config->ceiling_color[1]
    // ,game->config->ceiling_color[2]
    // ,game->start_parcing_map);
    int i = 0;
    while (i <= 5)
    {
        if (game->config->check_duplicate[i] != 1)
            return (ft_putendl_fd(ERROR_DUP, 2), 0);
        i++;
    }
    if (!filling_map(game, argv[1]))
        return (0);
    if (!cheack_lines(game))
        return (0);
    printf("player x : %d | player y : %d \n", game->player_x, game->player_y);
    int j = 0;
    while (game->map->grid[j])
    {
        printf("%s\n", game->map->grid[j]);
        j++;
    }
    // printf("\n[%d]\n[%d]\n[%d]\n[%d]\n[%d]\n[%d]\n", game->config->check_duplicate[0], game->config->check_duplicate[1], game->config->check_duplicate[2]
    // , game->config->check_duplicate[3], game->config->check_duplicate[4], game->config->check_duplicate[5]);
    return (1);
}


        // else  if (!ft_strncmp(str, "F", 1))
        // {
        //     if (!parce_and_filling_line(game->config->no_texture, str))
        //         return (0);
        // }
        //     // printf("F  - %s", str);
        // else  if (!ft_strncmp(str, "C", 1))
        // {
        //     if (!parce_and_filling_line(game->config->no_texture, str))
        //         return (0);
        // }
            // printf("C  - %s", str);
        // else  if (!ft_strncmp(str, "1", 1) || !ft_strncmp(str, "0", 1))
        //     printf("--- %s", str);