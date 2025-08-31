/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:42:43 by hkhairi           #+#    #+#             */
/*   Updated: 2025/08/31 20:48:01 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	check_name(char *str)
{
	int		lent_path;
	char	*constant;

	constant = ".cub";
	lent_path = ft_strlen(str);
	if (lent_path < 4)
		return (ft_putendl_fd(NAME_SHOURT, 2), 0);
	if (!ft_strcmp(str + (lent_path - 4), constant))
		return (ft_putendl_fd(ERROR_EXTENTION, 2), 0);
	return (1);
}

int	start_parcing(int argc, char *argv[], t_game *game)
{
	int	i;

	i = 0;
	if (argc != 2)
	{
		if (argc < 2)
			return (ft_putendl_fd(NEED_ARG, 2), 0);
		return (ft_putendl_fd(ERROR_ARG, 2), 0);
	}
	if (!check_name(argv[1]))
		return (0);
	if (!filling_game(argv, game))
		return (0);
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
	return (1);
}
