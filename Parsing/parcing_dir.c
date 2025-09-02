/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:06:08 by hkhairi           #+#    #+#             */
/*   Updated: 2025/09/01 10:07:24 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	updated_number_index(int *index, char *prifex)
{
	if (ft_strcmp(prifex, "NO"))
		(*index)++;
	else if (ft_strcmp(prifex, "SO"))
		(*index)++;
	else if (ft_strcmp(prifex, "WE"))
		(*index)++;
	else if (ft_strcmp(prifex, "EA"))
		(*index)++;
	else if (ft_strcmp(prifex, "F"))
		(*index)++;
	else if (ft_strcmp(prifex, "C"))
		(*index)++;
}

int	parce_and_filling_line(char **texter, char *str, int *index, char *prifex)
{
	int	i;
	int	j;

	i = 0;
	updated_number_index(index, prifex);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!str[i])
		return (ft_putendl_fd(NOT_FOUND, 2), 0);
	j = i;
	while (str[j] && str[j] != ' ' && str[j] != '\t' && str[j] != '\n')
		j++;
	if (*texter)
		free(*texter);
	*texter = ft_substr(str, i, j);
	if (!texter)
		return (0);
	while (str[j] && (str[j] == ' ' || str[j] == '\t' || str[j] == '\n'))
		j++;
	if (str[j])
		return (ft_putendl_fd(ERROR_VALUE, 2), 0);
	return (1);
}

int	check_diection_texter(t_game *game, char *str)
{
	if (!ft_strncmp(str, "NO", 2))
	{
		if (!parce_and_filling_line(&game->config->no_texture, str + 2,
				&game->config->check_duplicate[0], "NO"))
			return (0);
	}
	else if (!ft_strncmp(str, "SO", 2))
	{
		if (!parce_and_filling_line(&game->config->so_texture, str + 2,
				&game->config->check_duplicate[1], "SO"))
			return (0);
	}
	else if (!ft_strncmp(str, "WE", 2))
	{
		if (!parce_and_filling_line(&game->config->we_texture, str + 2,
				&game->config->check_duplicate[2], "WE"))
			return (0);
	}
	else if (!ft_strncmp(str, "EA", 2))
	{
		if (!parce_and_filling_line(&game->config->ea_texture, str + 2,
				&game->config->check_duplicate[3], "EA"))
			return (0);
	}
	return (1);
}
