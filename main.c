/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:11:48 by hkhairi           #+#    #+#             */
/*   Updated: 2025/08/29 10:41:52 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./cub.h"

int main(int argc, char *argv[])
{
    t_game *game;
    void *mlx_ptr;
    void *win_ptr; 

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
