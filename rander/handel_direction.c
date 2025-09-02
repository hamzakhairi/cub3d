#include "../cub.h"

int handel_move(int val, int set)
{
    static int x = 0;
    if (set == 0)
        x = val;
    else
        return x;
    return (-1);
}

int mouse_move_player(int x, int y, void *struct_game)
{
    t_game      *game;
    static int  start = 0;

    game = (t_game *)struct_game;
    if (start == 0)
    {
        handel_move(x, 0);
        start = 1;
    }
    else
    {
        if ((handel_move(0, 1) - x) < 0)
        {
            game->map->key = KEY_RIGHT;
            moving(KEY_RIGHT, game);
            handel_move(x, 0);
        }
        else if ((handel_move(0, 1) - x) > 0)
        {
            game->map->key = KEY_LEFT;
            moving(KEY_LEFT, game);
            handel_move(x, 0);
        }        
    }
    return (0);
}


