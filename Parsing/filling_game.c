/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:12:05 by hkhairi           #+#    #+#             */
/*   Updated: 2025/08/31 22:01:14 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	check_if_start_prcing_map(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!str[i])
		return (1);
	if (str[i] == '1' || str[i] == '0')
		return (0);
	if ((str[i] == 'N' && str[i + 1] != 'O')
		|| (str[i] == 'S' && str[i + 1] != 'O')
		|| (str[i] == 'E' && str[i + 1] != 'A')
		|| (str[i] == 'W' && str[i + 1] != 'E'))
		return (0);
	return (1);
}

int	filling_game(char *argv[], t_game *game)
{
	int		fd;
	char	*str;
	int		start;

	fd = open(argv[1], O_RDONLY, 0644);
	if (fd < 0)
		return (ft_putendl_fd(NOT_FOUND, 2), 0);
	str = get_next_line(fd);
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
			(get_next_line(-1), free(str));
			break ;
		}
		(free(str), start++);
		str = get_next_line(fd);
	}
	return (1);
}
