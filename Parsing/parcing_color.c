/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 21:57:41 by hkhairi           #+#    #+#             */
/*   Updated: 2025/08/31 21:57:43 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub.h"

int extarct_rgb(int *color, char *str)
{
    int i = 0;
    int j = 0;
    int index = 0;

    while (str[i])
    {
        if (str[i] == ',')
            j++;
        if (!ft_isdigit(str[i]) && str[i] != ',')
            return (ft_putendl_fd(ERROR_VALUE, 2), 0);
        i++;
    }
    if (j != 2)
        return (ft_putendl_fd(ERROR_VALUE, 2), 0);
    i = 0;
    while (str[i])
    {
        j = i;
        while (str[i] && str[i] != ',')
            i++;
        if (index >= 3 || (j == i))
            return (ft_putendl_fd(ERROR_VALUE, 2), 0);
        color[index] = ft_mini_atoi(str, j, i);
        if (color[index] < 0 || color[index] > 255)
            return (ft_putendl_fd(ERROR_VALUE, 2), 0);
        index++;
        if (str[i])
            i++;
    }
    return (index == 3);
}

int check_cloros(t_game *game, char *str)
{
    char *new;

    new = NULL;
    if (!ft_strncmp(str, "F", 1))
    {
        if (!parce_and_filling_line(&new, str + 1, &game->config->check_duplicate[4], "F"))
        {
            if (new)
                free(new);
            return (0);
        }
        if (!extarct_rgb(game->config->floor_color, new))
            return (free(new), 0);
    }
    else if (!ft_strncmp(str, "C", 1))
    {
        if (!parce_and_filling_line(&new, str + 1, &game->config->check_duplicate[5], "C"))
        {
            if (new)
                free(new);
            return (0);
        }
        if (!extarct_rgb(game->config->ceiling_color, new))
            return (free(new), 0);
    }
    if (new)
        free(new);
    return (1);
}
