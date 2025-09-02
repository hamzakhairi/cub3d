/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:11:48 by hkhairi           #+#    #+#             */
/*   Updated: 2025/09/02 22:45:21 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./cub.h"

// void check_leaks(void)
// {
//     system("leaks cub");
// }

int main(int argc, char *argv[])
{
    // atexit(check_leaks);
    t_game *game;

    game = malloc(sizeof(t_game));
    if (!game)
        return (1);
    if (!init_struct(game))
        return (free_game(game), 1);
    if (!start_parcing(argc, argv, game))
    {
        printf("********************----***\n");
        return (free_game(game), 1);
    }
    // if (!start_randering(game))
    //     return (1);
    // free_game(game);
    return (0);
}
