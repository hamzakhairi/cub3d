/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:42:43 by hkhairi           #+#    #+#             */
/*   Updated: 2025/07/02 18:16:36 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub.h"

int check_name(char *str)
{
	int		lent_path;
	char	*constant;

	constant = ".cub";
	lent_path = ft_strlen(str);
	if (lent_path < 4)
		return (ft_putendl_fd(NAME_SHOURT, 2), 0);
	if (!ft_strcmp(str + (lent_path - 4), constant))
		return (ft_putendl_fd(ERROR_EXTENTION, 2), 0);
    return 1;
}

int start_parcing(int argc, char *argv[], t_game *game)
{
    if (argc != 2)
    {
        if (argc < 2)
            return (ft_putendl_fd(NEED_ARG, 2), 0);
        return (ft_putendl_fd(ERROR_ARG, 2), 0);
    }
    if (!check_name(argv[1]))
        return (0);
    if (!filling_game(argc, argv, game))
        return (0);
    return (1);
}
