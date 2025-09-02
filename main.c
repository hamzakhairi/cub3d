/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:11:48 by hkhairi           #+#    #+#             */
/*   Updated: 2025/09/02 10:14:37 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./cub.h"

int main(int argc, char *argv[])
{
    t_game *game;

    game = malloc(sizeof(t_game));
    if (!game)
        return (1);
    if (!init_struct(game))
        return (0);
    if (!start_parcing(argc, argv, game))
        return (0);
    if (!start_randering(game))
        return (0);
    // free_game(game);
    return (0);
}
