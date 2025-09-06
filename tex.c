#include "../cub.h"

void	draw_line_height(t_game *game, int x)
{
	float	tex_step;
	float	tex_pos;
	int		y;
	t_tex	*tex;
	float	wall_hit;
	int		tex_x;
	int		tex_y;
	int		color;

	tex_pos = 0;
	y = 0;
	tex = get_wall_texture(game, x);
	wall_hit = calculate_wall_hit_x(game, x, game->map->dis[x]);
	tex_x = (int)((wall_hit / SIZE) * tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;

	if (game->wall_top < 0)
		tex_pos = (0 - game->wall_top) * tex_step;

	if (game->wall_top < 0)
		game->wall_top = 0;

	if (game->wall_bottom >= HEIGHT_3D)
		game->wall_bottom = HEIGHT_3D - 1;

	tex_step = (float)tex->height / game->wall_height;
	while (y < HEIGHT_3D)
	{
		if (y < game->wall_top)
			put_pixel(game, x, y, 0xFF0000);
		else if (y <= game->wall_bottom)
		{
			tex_y = (int)tex_pos;
			if (tex_y >= tex->height)
				tex_y = tex->height - 1;
			if (tex_y < 0)
				tex_y = 0;
			color = get_tex_pixel(tex, tex_x, tex_y);
			put_pixel(game, x, y, color);
			tex_pos += tex_step;
		}
		else
			put_pixel(game, x, y, 0x8B4513);
		y++;
	}
}