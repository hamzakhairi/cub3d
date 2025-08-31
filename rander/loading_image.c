
#include "../cub.h"


char *path_image_image(char *PRE_FIX, int n)
{
    int len_prefix = ft_strlen(PRE_FIX);
    char *index_str = ft_itoa(n);
    if (!index_str)
        return NULL;
    int len_index = ft_strlen(index_str);
    int total_len = len_prefix + len_index + 4;
    char *str = malloc(total_len + 1);
    if (!str)
    {
        free(index_str);
        return NULL;
    }
    memcpy(str, PRE_FIX, len_prefix);
    memcpy(str + len_prefix, index_str, len_index);
    memcpy(str + len_prefix + len_index, ".xpm", 4);
    str[total_len] = '\0';
    free(index_str);
    return str;
}

int loading_image(t_game *game)
{
    int img_width, img_height;
    int i;

    game->img_player = malloc(sizeof(t_player));
    if (!game->img_player)
        return 0;

    game->img_player->images_walk = malloc(sizeof(void *) * 42);
    if (!game->img_player->images_walk)
        return 0;
    game->img_player->images_counter_walk = 41;
    game->img_player->current_image = 0;
    i = 0;
    while (i < game->img_player->images_counter_walk)
    {
        char *str = path_image_image(PATH_WLKING, i + 1);
        game->img_player->images_walk[i] =
            mlx_xpm_file_to_image(game->mlx_ptr, str, &img_width, &img_height);
        free(str);
        if (!game->img_player->images_walk[i])
        {
            printf("Error Walk %d \n", i);
            return 0;
        }
        i++;
    }

    game->img_player->images_shout = malloc(sizeof(void *) * 3);
    if (!game->img_player->images_shout)
        return 0;
    game->img_player->images_counter_shot = 2;
    i = 0;
    while (i < game->img_player->images_counter_shot)
    {
        char *str = path_image_image(PATH_SOTING, i + 1);
        game->img_player->images_shout[i] =
            mlx_xpm_file_to_image(game->mlx_ptr, str, &img_width, &img_height);
        free(str);
        if (!game->img_player->images_shout[i])
        {
            printf("Error Shot %d \n", i);
            return 0;
        }
        i++;
    }
    game->img_player->images_Feeding = malloc(sizeof(void *) * 42);
    if (!game->img_player->images_Feeding)
        return 0;
    game->img_player->images_counter_Feeding = 41;
    i = 0;
    while (i < game->img_player->images_counter_Feeding)
    {
        char *str = path_image_image(PATH_FEEDING, i + 1);
        game->img_player->images_Feeding[i] =
            mlx_xpm_file_to_image(game->mlx_ptr, str, &img_width, &img_height);
        free(str);
        if (!game->img_player->images_Feeding[i])
        {
            printf("Error feeding %d \n", i);
            return 0;
        }
        i++;
    }

    game->img_player->frame = 0;
    game->img_player->is_state = 0;
    return 1;
}

void update_state(t_game *game)
{
    int max_frames;

    game->img_player->frame++;
    if (game->img_player->frame >= SPEED)
    {
        game->img_player->frame = 0;
        game->img_player->current_image++;

        if (game->img_player->is_state == 0)
            max_frames = game->img_player->images_counter_walk;
        else if (game->img_player->is_state == 1)
            max_frames = game->img_player->images_counter_shot;
        else
            max_frames = game->img_player->images_counter_Feeding;

        if (game->img_player->current_image >= max_frames)
        {
            game->img_player->current_image = 0;
            game->img_player->is_state = 0;
        }
    }
}

void render_images(t_game *game)
{
    if (game->img_player->is_state == 0)
        mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
            game->img_player->images_walk[game->img_player->current_image],
            (WIDTH_3D) / 2 - (WIDTH_3D / 4),
            (HEIGHT_3D - 400) + (HEIGHT_3D - 400) / 16);

            // HEIGHT_3D + 16);
    else if (game->img_player->is_state == 1)
        mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
            game->img_player->images_shout[game->img_player->current_image],
            (WIDTH_3D) / 2 - (WIDTH_3D / 4),
            (HEIGHT_3D - 400) + (HEIGHT_3D - 400) / 16);

            // HEIGHT_3D + 16);
    else
        mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
            game->img_player->images_Feeding[game->img_player->current_image],
            (WIDTH_3D) / 2 - (WIDTH_3D / 4),
            (HEIGHT_3D - 400) + (HEIGHT_3D - 400) / 16);
}


int loop_inimation(t_game *game)
{
    create_put_image_to_window(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img_ptr, 0, 0);
    update_state(game);
    render_images(game);
    return 0;
}
