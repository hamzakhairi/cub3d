


int loading_image(t_game *game)
{
    int w_img;
    int h_img;

    game->
}

	mlx_hook(game->win_ptr, 6, 0L, mouse_move_player, game);


void Move_player(t_game *game, float y, float x);

/*
	bonus
*/
int mouse_move_player(int x, int y, void *struct_game);
