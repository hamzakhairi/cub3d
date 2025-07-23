
# include "../cub.h"

int ft_close(t_game *game)
{
    free_game(game);
    exit(0);
    return (0);
}

int load_images(t_game *game)
{
	int	img_width;
	int	img_height;

	img_width = 0;
	img_height = 0;
    game->img_no = mlx_xpm_file_to_image(game->mlx_ptr,
            game->config->no_texture, &img_width, &img_height);
    game->img_so = mlx_xpm_file_to_image(game->mlx_ptr,
            game->config->no_texture, &img_width, &img_height);
    game->img_we = mlx_xpm_file_to_image(game->mlx_ptr,
            game->config->no_texture, &img_width, &img_height);
    game->img_wa = mlx_xpm_file_to_image(game->mlx_ptr,
            game->config->no_texture, &img_width, &img_height);
    if (!game->img_so || !game->img_no
        || !game->img_wa || !game->img_we)
        return (ft_putendl_fd(ERROR_IMG, 2), 0);
    return (1);
}

int init_game(t_game *game)
{
    game->mlx_ptr = mlx_init();
    if (!game->mlx_ptr)
        return (ft_putendl_fd(ERROR_RENDER, 2), 1);
    game->win_ptr = mlx_new_window(game->mlx_ptr, 800, 600, "cub3D Window");
    if (!game->win_ptr)
        return (ft_putendl_fd(ERROR_RENDER, 2), 0);
    if (!load_images(game))
        return (0);
    return (1);
}

# define TILE_SIZE 32

void	put_image(t_game *game, void *img, int x, int y)
{
	if (img)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, img,
			x * TILE_SIZE, y * TILE_SIZE);
}

void	validate_put_game(t_game *game, int x, int y, char c)
{
	void	*img;

	img = NULL;
	if ('1' == c)
		img = game->img_so;
	else if ('0' == c)
		img = game->img_no;
	else if ('N' == c)
		img = game->img_we;
	put_image(game, img, x, y);
}

void	render_map(t_game	*game)
{
	int		y;
	int		x;

	y = 0;
	x = 0;
	while (game->map->grid[y])
	{
		x = 0;
		while (game->map->grid[y][x])
		{
			validate_put_game(game, x, y, game->map->grid[y][x]);
			x++;
		}
		y++;
	}
}

int start_randering(t_game *game)
{
    if (!init_game(game))
        return (0);
    render_map(game);
    mlx_hook(game->win_ptr, 17, 0L, ft_close, game);
    mlx_loop(game->mlx_ptr);
    return (1);
}

