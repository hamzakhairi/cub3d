#include "../cub.h"
int get_tex_pixel(t_tex *tex, int x, int y)
{
    char *dst;

    if (x < 0 || y < 0 || x >= tex->width || y >= tex->height)
        return 0xFF00FF; // debug: magenta if error

    dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
    return (*(unsigned int *)dst);
}

void	draw_line_height(t_game *game, int x)
{
	int	y;
	int color;
	int tex_x;
	int tex_y;
	int d;
	int size_wall;
	int next;
	int i;

	y = 0;
	tex_x = x;
	tex_y = 0;
	while (y < HEIGHT_3D)
	{
		if (y < game->wall_top)
			put_pixel(game, x, y, 0xFF0000);
		else if (y < game->wall_top + game->wall_height)
		{
			size_wall = ((int)game->wall_height - game->wall_top);
			// if (game->map->wall_direction[x] == 1)
			// {
			color = get_tex_pixel(&game->img_east, tex_x, tex_y);
			if(game->img_east.height < size_wall)
			{
				next = game->img_east.height / (size_wall - game->img_east.height);
				i = 0;
				while (i < next && y < game->wall_top + game->wall_height)
				{
					put_pixel(game, x, y, color);//Black
					i++;
					y++;
				}
				tex_y++;
			}
			else
			{
				next = game->img_east.height / (game->img_east.height - size_wall);
				color = get_tex_pixel(&game->img_east, tex_x, tex_y);
				put_pixel(game, x, y, color);//Black
				tex_y += next;
			}
			if(game->img_east.height == tex_y)
			{
				while (y < game->wall_top + game->wall_height)
				{
					put_pixel(game, x, y, color);//Black
					y++;
				}
				y--;
			}
			// }
			// else if (game->map->wall_direction[x] == 2)
			// {
			// 	color = get_tex_pixel(&game->img_south, x, y);
			// 	put_pixel(game, x, y, color);//White
			// }
			// else if ((int)game->map->wall_direction[x] == 3)
			// {
			// 	color = get_tex_pixel(&game->img_north, x, y);
			// 	put_pixel(game, x, y, color);//Blue
			// }
			// else if ((int)game->map->wall_direction[x] == 4)
			// {
			// 	color = get_tex_pixel(&game->img_west, x, y);
			// 	put_pixel(game, x, y, color);//green
			// }
		}
		else
			put_pixel(game, x, y, 0x8B4513);
		y++;
	}
}


void	draw_line_height(t_game *game, int x)
{
	int	y;
	int color;
	int tex_x;
	int tex_y;
	int d;
	int size_wall;
	int next;
	int i;
    t_tex *tex;

	y = 0;
	tex_x = x;
	tex_y = 0;
	while (y < HEIGHT_3D)
	{
		if (y < game->wall_top)
			put_pixel(game, x, y, 0xFF0000);
		else if (y < game->wall_top + game->wall_height)
		{
			tex = &game->img_west;
		
			// tex_x يعتمد على مكان الضربة في الجدار (wall hit point)
			float wall_x;
			if (game->map->wall_direction[x] == 1 || game->map->wall_direction[x] == 3)
			    wall_x = game->player_y + game->map->dis[x] * sin(game->map->angle);
			else
			    wall_x = game->player_x + game->map->dis[x] * cos(game->map->angle);
		
			wall_x -= floor(wall_x);
			tex_x = (int)(wall_x * tex->width);
			
			// ارسم الخط
			for (y = game->wall_top; y < game->wall_bottom; y++)
			{
			    int d = y * 256 - HEIGHT_3D * 128 + game->wall_height * 128;
			    tex_y = ((d * tex->height) / game->wall_height) / 256;
			    color = get_tex_pixel(tex, tex_x, tex_y);
			    put_pixel(game, x, y, color);
			}
			
		}
		else
			put_pixel(game, x, y, 0x8B4513);
		y++;
	}
}





void	image_3d(t_game *game)
{
	int		x;
	float	cpy_angle;

	x = 0;
	game->distance_plane = (WIDTH_3D / 2) / tanf(FOV / 2);
	cpy_angle = game->map->angle - FOV / 2;
	x = 0;
	while (x < WIDTH_3D)
	{
		// Fix fisheye effect by using perpendicular distance
		game->corrected_distance = game->map->dis[x] * cosf(game->map->angle - (game->map->angle - FOV / 2 + (x * FOV / WIDTH_3D)));
		game->wall_height = (SIZE / game->corrected_distance) * game->distance_plane;
		game->wall_top = (HEIGHT_3D / 2) - (game->wall_height / 2);
		game->wall_bottom = (HEIGHT_3D / 2) + (game->wall_height / 2);
		if (game->wall_top < 0)
			game->wall_top = 0;
		if (game->wall_bottom >= HEIGHT_3D)
			game->wall_bottom = HEIGHT_3D - 1;
		draw_line_height(game, x);
		x++;
	}
}