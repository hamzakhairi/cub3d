#include "../cub.h"

void get_horizontal(t_game *game)
{
	float Yh_step;
	float Xh_step;

	Yh_step = SIZE;
	if(game->map->RayFacingUp)
		Yh_step *= -1;
	Xh_step = SIZE / tanf(game->map->angle);
	if(game->map->RayFacingLeft && Xh_step > 0)
		Xh_step *= -1;
	if(game->map->RayFacingRight && Xh_step < 0)
		Xh_step *= -1;

	game->map->Y_horizontal += Yh_step;
	game->map->X_horizontal += Xh_step;
}

void get_vertical(t_game *game)
{
	float Yv_step;
	float Xv_step;

	Xv_step = SIZE;
	if (game->map->RayFacingLeft)
		Xv_step *= -1;
	Yv_step = SIZE * tanf(game->map->angle);
	if (game->map->RayFacingUp && Yv_step > 0)
		Yv_step *= -1;
	if(game->map->RayFacingDown && Yv_step < 0)
		Yv_step *= -1;

	game->map->X_vertical += Xv_step;
	game->map->Y_vertical += Yv_step;
}

void directoin_player(t_game *game)
{
    game->map->RayFacingDown  = game->map->angle > 0 && game->map->angle < M_PI;
	game->map->RayFacingUp    = !game->map->RayFacingDown;
	game->map->RayFacingRight = game->map->angle < M_PI / 2 || game->map->angle > 3 * M_PI / 2;
	game->map->RayFacingLeft  = !game->map->RayFacingRight;
}

float ray_casting(t_game *game, float ray_angle, int ray_count)
{
	float dis_v = INFINITY;
	float dis_h = INFINITY;
	float temp_angle = game->map->angle;
	
	game->map->angle = ray_angle;
	directoin_player(game);
	game->map->Y_horizontal = floorf(game->player_pixl_y / SIZE) * SIZE;
	if (game->map->RayFacingDown)
  		game->map->Y_horizontal += SIZE;
	game->map->X_horizontal = game->player_pixl_x + (game->map->Y_horizontal - game->player_pixl_y) / tanf(ray_angle);
	while (1)
	{
		int Xh = (int)game->map->X_horizontal / SIZE;
		int Yh = (int)game->map->Y_horizontal / SIZE;
		if (Xh < 0 || Yh < 0 || Xh >= (game->map->width / SIZE) || Yh >= (game->map->height / SIZE))
			break;
		
		int checkY = Yh;
		if (game->map->RayFacingUp)
			checkY = Yh - 1;
		
		if (checkY >= 0 && checkY < (game->map->height / SIZE) && game->map->grid[checkY][Xh] == '1')
		{
			dis_h = sqrtf(powf(game->map->X_horizontal - game->player_pixl_x, 2) + powf(game->map->Y_horizontal - game->player_pixl_y, 2));
			break;
		}
		get_horizontal(game);
	}

	game->map->X_vertical = floorf(game->player_pixl_x / SIZE) * SIZE;
	if (game->map->RayFacingRight)
		game->map->X_vertical += SIZE;
	game->map->Y_vertical = game->player_pixl_y + (game->map->X_vertical - game->player_pixl_x) * tanf(ray_angle);
	while (1)
	{
		int Xv = (int)game->map->X_vertical / SIZE;
		int Yv = (int)game->map->Y_vertical / SIZE;

		if (Xv < 0 || Yv < 0 || Xv >= (game->map->width / SIZE) || Yv >= (game->map->height / SIZE))
			break;
		
		int checkX = Xv;
		if (game->map->RayFacingLeft)
			checkX = Xv - 1;
		
		if (checkX >= 0 && checkX < (game->map->width / SIZE) && game->map->grid[Yv][checkX] == '1')
		{
			dis_v = sqrtf(powf(game->map->X_vertical - game->player_pixl_x, 2) + powf(game->map->Y_vertical - game->player_pixl_y, 2));
			break;
		}
		get_vertical(game);
	}
	directoin_player(game);
	game->map->angle = temp_angle;

	game->map->d_X[ray_count] = 0;
	if (dis_v < dis_h)
	{
		int x = (int)game->map->X_vertical / SIZE;
		int y = (int)game->map->Y_vertical / SIZE;
		
		if(game->map->RayFacingUp && game->map->RayFacingRight)
		{
			game->map->d_X[ray_count] = 2;
		}
		else if(game->map->RayFacingUp && game->map->RayFacingLeft)
		{
			game->map->d_X[ray_count] = 3;
		}
		else if(game->map->RayFacingDown && game->map->RayFacingLeft)
			game->map->d_X[ray_count] = 3;
		else if(game->map->RayFacingDown && game->map->RayFacingRight)
			game->map->d_X[ray_count] = 2;
		return dis_v;
	}
	else
	{
		if(game->map->RayFacingUp)
			game->map->d_X[ray_count] = 1;
		else if (game->map->RayFacingDown)
			game->map->d_X[ray_count] = 4;
		return dis_h;
	}
}

void    setup_player(t_game *game)
{
    int    i;
    int    j;

    int    r = 8;
    int    center_x = game->player_pixl_x;
    int    center_y = game->player_pixl_y;

    i = -r;
    while (i <= r)
    {
        j = -r;
        while (j <= r)
        {
            if (i * i + j * j <= r * r)
                put_pixel(game, center_x + j, center_y + i, 0x00FF0000);
            j++;
        }
        i++;
    }
}

void image_3D(t_game *game)
{
	int y = 0;
	int x = 0;
	float distance_plane;
	float wall_height;
	int wall_top;
	int wall_bottom;
	int ceiling_color;
	int floor_color;
	float cpy_angle;

	ceiling_color = (game->config->ceiling_color[0] << 16) | 
					(game->config->ceiling_color[1] << 8) | 
					game->config->ceiling_color[2];
	floor_color = (game->config->floor_color[0] << 16) | 
				  (game->config->floor_color[1] << 8) | 
				  game->config->floor_color[2];

	distance_plane = (WIDTH_3D / 2) / tanf(FOV / 2);
	cpy_angle = game->map->angle - FOV / 2;
	x = 0;
	while(x < WIDTH_3D)
	{
		// Fix fisheye effect by using perpendicular distance
		float corrected_distance = game->map->dis[x] * cosf(game->map->angle - (game->map->angle - FOV / 2 + (x * FOV / WIDTH_3D)));
		
		wall_height = (SIZE / corrected_distance) * distance_plane;
		wall_top = (HEIGHT_3D / 2) - (wall_height / 2);
		wall_bottom = (HEIGHT_3D / 2) + (wall_height / 2);
		
		if (wall_top < 0)
			wall_top = 0;
		if (wall_bottom >= HEIGHT_3D)
			wall_bottom = HEIGHT_3D - 1;
		
		y = 0;
		while (y < HEIGHT_3D)
		{
			if (y < wall_top)
				put_pixel(game, x, y, ceiling_color);
			else if (y < wall_top + wall_height)
			{
				if (game->map->d_X[x] == 1)
					put_pixel(game, x, y, 0x000000);//Black
				else if (game->map->d_X[x] == 2)
					put_pixel(game, x, y, 0xFFFFFF);//White
				else if ((int)game->map->d_X[x] == 3)
					put_pixel(game, x, y, 0x0000FF);//Blue
				else if ((int)game->map->d_X[x] == 4)
					put_pixel(game, x, y, 0x00FF00);//green
				else
					put_pixel(game, x, y, 0xFFFFFF);
			}
			else
				put_pixel(game, x, y, floor_color);
			y++;
		}
		x++;
	}
}

void setup_ray(t_game *game)
{

    float ray_angle;
	int ray_count = 0;
	float angle_step = FOV / WIDTH_3D;

	ray_angle = game->map->angle - FOV / 2;
	
	while(ray_count < WIDTH_3D)
	{
		if (ray_angle < 0)
			ray_angle += 2 * M_PI;
		if (ray_angle >= 2 * M_PI)
			ray_angle -= 2 * M_PI;

		game->map->dis[ray_count] = ray_casting(game, ray_angle, ray_count);
		ray_angle += angle_step;
		ray_count++;
	}
	image_3D(game);
}


void setup1_ray(t_game *game)
{
    float new_x;
	float new_y;
	float cpy_angle;
    float i;
	int face;
	float angle_step = FOV / WIDTH_3D;
	cpy_angle = game->map->angle - FOV / 2;
	while(cpy_angle <= game->map->angle + FOV / 2)
	{
		i = 1;
		new_x = game->player_pixl_x / 4 + (cosf(cpy_angle) * i);
		new_y = game->player_pixl_y / 4 + (sinf(cpy_angle) * i);
		while(1)
		{
			new_x = game->player_pixl_x / 4 + (cosf(cpy_angle) * i);
			if (game->map->grid[((int)new_y * 4) / SIZE][((int)new_x * 4) / SIZE] == '1')
				break ;
			new_y = game->player_pixl_y / 4  + (sinf(cpy_angle) * i);
			if (game->map->grid[((int)new_y * 4) /SIZE][((int)new_x * 4) / SIZE] == '1')
				break ;
			put_pixel(game, (int)new_x, (int)new_y, 0x00FFFF00);
			i++;
		}
		cpy_angle += angle_step;
	}

}



