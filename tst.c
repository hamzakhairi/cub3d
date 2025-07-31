// void Move_game(t_game *game, int y, int x, int key)
// {
// 	int a;
// 	int b;
// 	int c;
// 	int d;
// 	if(key == KEY_A)
// 	{
// 		a = (y - 12) / SIZE;
// 		b = (x - 12) / SIZE;
// 		c = (y + 12) / SIZE;
// 		d = (x - 12) / SIZE;
// 	}
// 	else if(key == KEY_S)
// 	{
// 		a = (y + 12) / SIZE;
// 		b = (x - 12) / SIZE;
// 		c = (y + 12) / SIZE;
// 		d = (x + 12) / SIZE;
// 	}
// 	else if (key == KEY_W)
// 	{
// 		a = (y - 12) / SIZE;
// 		b = (x - 12) / SIZE;
// 		c = (y - 12) / SIZE;
// 		d = (x + 12) / SIZE;
// 	}
// 	else if (key == KEY_D)
// 	{
// 		a = (y - 12) / SIZE;
// 		b = (x + 12) / SIZE;
// 		c = (y + 12) / SIZE;
// 		d = (x + 12) / SIZE;
// 	}
// 	if(game->map->grid[a][b] != '1' && game->map->grid[c][d] != '1')
// 	{
// 		game->player_pixl_y = y;
// 		game->player_pixl_x = x;
// 	}
// }