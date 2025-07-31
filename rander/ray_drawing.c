#include "../cub.h"

void setup_ray(t_game *game)
{
	int a_y;
	int b_x;
	int c_y;
	int d_x;
	int t_y;
	int r_x;
	int m_y;
	int n_x;
    float new_x;
	float new_y;
    int i;
    i = 1;
    while (1)
    {
        new_x = game->player_pixl_x + (cosf(game->map->angle) * i);
		new_y = game->player_pixl_y + (sinf(game->map->angle) * i);
        put_pixel(game, new_x, new_y, 0x00FFFF00);
        a_y = (new_y) / SIZE;
	    b_x = (new_x) / SIZE;
	    c_y = (new_y) / SIZE;
	    d_x = (new_x) / SIZE;
	    t_y = (new_y) / SIZE;
	    r_x = (new_x) / SIZE;
	    m_y = (new_y) / SIZE;
	    n_x = (new_x) / SIZE;
        if (game->map->grid[a_y][b_x] == '1' || game->map->grid[c_y][d_x] == '1'
		&& game->map->grid[t_y][r_x] == '1' || game->map->grid[m_y][n_x] == '1')
	    {
	    	break ;
	    }
        i++;
    }
}