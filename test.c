/* Fixed texture rendering function */
#include "../cub.h"

// Fixed texture pixel getter with proper bounds checking
int get_tex_pixel(t_tex *tex, int x, int y)
{
    char *dst;

    // Clamp coordinates to texture bounds
    if (x < 0) x = 0;
    if (x >= tex->width) x = tex->width - 1;
    if (y < 0) y = 0;
    if (y >= tex->height) y = tex->height - 1;

    dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
    return (*(unsigned int *)dst);
}

// Select the correct texture based on wall direction
t_tex *get_wall_texture(t_game *game, int ray_index)
{
    int wall_dir = game->map->wall_direction[ray_index];
    
    switch (wall_dir)
    {
        case 1: return &game->img_north;  // North wall
        case 2: return &game->img_east;   // East wall  
        case 3: return &game->img_west;   // West wall
        case 4: return &game->img_south;  // South wall
        default: return &game->img_north; // Fallback
    }
}

// Calculate wall hit position for texture X coordinate - FIXED VERSION
float calculate_wall_hit_x(t_game *game, int ray_index, float distance)
{
    float ray_angle = game->map->angle - FOV / 2 + (ray_index * FOV / WIDTH_3D);
    float hit_x, hit_y;
    float wall_x;
    
    // Calculate the exact hit point
    hit_x = game->player_pixl_x + distance * cosf(ray_angle);
    hit_y = game->player_pixl_y + distance * sinf(ray_angle);
    
    // Get wall direction for this ray
    int wall_dir = game->map->wall_direction[ray_index];
    
    // Calculate texture X coordinate based on which wall face we hit
    if (wall_dir == 1) // North wall (horizontal wall, top face)
    {
        wall_x = fmod(hit_x, SIZE);
        if (wall_x < 0) wall_x += SIZE;
    }
    else if (wall_dir == 4) // South wall (horizontal wall, bottom face)  
    {
        wall_x = fmod(hit_x, SIZE);
        if (wall_x < 0) wall_x += SIZE;
        wall_x = SIZE - wall_x; // Reverse for correct texture orientation
    }
    else if (wall_dir == 2) // East wall (vertical wall, right face)
    {
        wall_x = fmod(hit_y, SIZE);
        if (wall_x < 0) wall_x += SIZE;
    }
    else if (wall_dir == 3) // West wall (vertical wall, left face)
    {
        wall_x = fmod(hit_y, SIZE);
        if (wall_x < 0) wall_x += SIZE;
        wall_x = SIZE - wall_x; // Reverse for correct texture orientation
    }
    else
    {
        wall_x = fmod(hit_x, SIZE);
        if (wall_x < 0) wall_x += SIZE;
    }
    
    return wall_x;
}

void draw_line_height(t_game *game, int x)
{
    int y = 0;
    t_tex *tex = get_wall_texture(game, x);
    
    // Calculate texture X coordinate with improved precision
    float wall_hit = calculate_wall_hit_x(game, x, game->map->dis[x]);
    int tex_x = (int)((wall_hit / SIZE) * tex->width);
    
    // Ensure tex_x is within bounds with proper wrapping
    while (tex_x < 0) tex_x += tex->width;
    while (tex_x >= tex->width) tex_x -= tex->width;
    
    // Calculate the ACTUAL wall bounds that will be drawn
    int draw_start = (game->wall_top < 0) ? 0 : game->wall_top;
    int draw_end = (game->wall_bottom >= HEIGHT_3D) ? HEIGHT_3D - 1 : game->wall_bottom;
    
    // Calculate texture step - this is key for fixing the warping!
    float tex_step = (float)tex->height / game->wall_height;
    
    // Calculate starting texture position
    float tex_pos = 0;
    if (game->wall_top < 0)
    {
        // If wall extends above screen, calculate which part of texture to start with
        tex_pos = (0 - game->wall_top) * tex_step;
    }
    
    while (y < HEIGHT_3D)
    {
        if (y < draw_start)
        {
            // Ceiling - use ceiling color from config
            int ceiling_color = (game->config->ceiling_color[0] << 16) | 
                               (game->config->ceiling_color[1] << 8) | 
                               game->config->ceiling_color[2];
            put_pixel(game, x, y, ceiling_color);
        }
        else if (y <= draw_end)
        {
            // Wall texture - using precise floating point calculation
            int tex_y = (int)tex_pos;
            
            // Clamp tex_y to texture bounds with proper wrapping
            while (tex_y < 0) tex_y += tex->height;
            while (tex_y >= tex->height) tex_y -= tex->height;
            
            int color = get_tex_pixel(tex, tex_x, tex_y);
            put_pixel(game, x, y, color);
            
            // Advance texture position
            tex_pos += tex_step;
        }
        else
        {
            // Floor - use floor color from config
            int floor_color = (game->config->floor_color[0] << 16) | 
                             (game->config->floor_color[1] << 8) | 
                             game->config->floor_color[2];
            put_pixel(game, x, y, floor_color);
        }
        y++;
    }
}

// Fixed ray direction calculation
void directoin_player(t_game *game)
{
    // Normalize angle to 0-2π range
    while (game->map->angle < 0) game->map->angle += 2 * M_PI;
    while (game->map->angle >= 2 * M_PI) game->map->angle -= 2 * M_PI;
    
    game->map->RayFacingDown = (game->map->angle > 0 && game->map->angle < M_PI);
    game->map->RayFacingUp = !game->map->RayFacingDown;
    game->map->RayFacingRight = (game->map->angle < M_PI / 2 || game->map->angle > 3 * M_PI / 2);
    game->map->RayFacingLeft = !game->map->RayFacingRight;
}

// Improved wall direction detection - FIXED VERSION
float distance_palyer_wall(t_game *game, float dis_v, float dis_h, int ray_count)
{
    if (dis_v < dis_h)
    {
        // Hit vertical wall - we need to determine if it's East or West face
        // Use the X coordinate of the hit point to determine the face
        float ray_angle = game->map->angle - FOV / 2 + (ray_count * FOV / WIDTH_3D);
        float hit_x = game->player_pixl_x + dis_v * cosf(ray_angle);
        
        // Check which side of the wall block we hit
        int wall_grid_x = (int)(hit_x / SIZE);
        float wall_center_x = (wall_grid_x + 0.5f) * SIZE;
        
        if (hit_x > wall_center_x)
            game->map->wall_direction[ray_count] = 2; // East wall (right side)
        else
            game->map->wall_direction[ray_count] = 3; // West wall (left side)
            
        return dis_v;
    }
    else
    {
        // Hit horizontal wall - we need to determine if it's North or South face
        float ray_angle = game->map->angle - FOV / 2 + (ray_count * FOV / WIDTH_3D);
        float hit_y = game->player_pixl_y + dis_h * sinf(ray_angle);
        
        // Check which side of the wall block we hit
        int wall_grid_y = (int)(hit_y / SIZE);
        float wall_center_y = (wall_grid_y + 0.5f) * SIZE;
        
        if (hit_y > wall_center_y)
            game->map->wall_direction[ray_count] = 4; // South wall (bottom side)
        else
            game->map->wall_direction[ray_count] = 1; // North wall (top side)
            
        return dis_h;
    }
}

// Fixed 3D rendering with proper fisheye correction and close wall handling
void image_3d(t_game *game)
{
    int x = 0;
    game->distance_plane = (WIDTH_3D / 2) / tanf(FOV / 2);
    
    while (x < WIDTH_3D)
    {
        // Calculate the ray angle for this column
        float ray_angle = game->map->angle - FOV / 2 + (x * FOV / WIDTH_3D);
        
        // Fix fisheye effect by using perpendicular distance
        game->corrected_distance = game->map->dis[x] * cosf(game->map->angle - ray_angle);
        
        // Prevent division by zero or extremely small distances
        if (game->corrected_distance < 0.1f)
            game->corrected_distance = 0.1f;
        
        // Calculate wall height on screen
        game->wall_height = (SIZE / game->corrected_distance) * game->distance_plane;
        
        // Limit maximum wall height to prevent extreme values
        if (game->wall_height > HEIGHT_3D * 3)
            game->wall_height = HEIGHT_3D * 3;
        
        // Calculate wall top and bottom positions
        game->wall_top = (HEIGHT_3D / 2) - (game->wall_height / 2);
        game->wall_bottom = (HEIGHT_3D / 2) + (game->wall_height / 2);
        
        // Draw the column
        draw_line_height(game, x);
        x++;
    }
}