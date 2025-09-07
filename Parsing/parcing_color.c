/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 21:57:41 by hkhairi           #+#    #+#             */
/*   Updated: 2025/09/07 12:30:41 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	extarct_rgb(int *color, char *str)
{
	int	i;
	int	start;
	int	index;

	i = 0;
	index = 0;
	while (str[i])
	{
		if ((!ft_isdigit(str[i]) && str[i] != ',') || index > 2)
			return (ft_putendl_fd(ERROR_VALUE, 2), 0);
		start = i;
		while (ft_isdigit(str[i]))
			i++;
		if (start == i || (str[i] && str[i] != ','))
			return (ft_putendl_fd(ERROR_VALUE, 2), 0);
		color[index] = ft_mini_atoi(str, start, i);
		if (color[index] < 0 || color[index] > 255)
			return (ft_putendl_fd(ERROR_VALUE, 2), 0);
		index++;
		if (str[i] == ',')
			i++;
	}
	return (index == 3);
}

void	free_new(char *new)
{
	if (new)
		free(new);
}

int	check_cloros(t_game *game, char *str)
{
	char	*new;

	new = NULL;
	if (!ft_strncmp(str, "F", 1))
	{
		if (!parce_and_filling_line(&new, str + 1,
				&game->config->check_duplicate[4], "F"))
			return (free_new(new), 0);
		if (!extarct_rgb(game->config->floor_color, new))
			return (free(new), 0);
	}
	else if (!ft_strncmp(str, "C", 1))
	{
		if (!parce_and_filling_line(&new, str + 1,
				&game->config->check_duplicate[5], "C"))
			return (free_new(new), 0);
		if (!extarct_rgb(game->config->ceiling_color, new))
			return (free(new), 0);
	}
	if (new)
		free(new);
	return (1);
}
