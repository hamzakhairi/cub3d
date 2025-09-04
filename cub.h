

# ifndef CUB_H
# define CUB_H

# include <mlx.h>
// # include "/home/rd_md_haker/Documents/mlx/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <limits.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>

# define SIZE 32
# define FOV 60 * M_PI / 180
# define ESC 53
# define SCALE 4

# define WIDTH_3D 1050
# define HEIGHT_3D 768
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ZOOM 6
# define KEY_Q 12
# define KEY_T 14
# define KEY_F 15
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define NUM_GAME_MOVES 8
# define SPEED 4
# define PLAYER_SIZE 4
# define DST_W_P 10
# define PATH_WLKING "./texter/player/rm_bg_walk/"
# define PATH_FEEDING "./texter/player/feeding/"
# define PATH_SOTING "./texter/player/xpm_shot/"

typedef struct s_config {
	char *no_texture;
	char *so_texture;
	char *we_texture;
	char *ea_texture;
	int *check_duplicate;
	int floor_color[3];
	int ceiling_color[3];
}		t_config;

typedef struct s_tex
{
    void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bpp;
    int     line_len;
    int     endian;
}   t_tex;


typedef struct s_map {
	char	**grid;
	float	dis[WIDTH_3D];
	int		key;
	float	angle;
	char	palyer;
	float	Y_vertical;
	float	X_vertical;
	float	Y_horizontal;
	float	X_horizontal;
	float	wall_direction[WIDTH_3D];
	int		width_angel;
	int		width;
	int		height;

	int		iszoom;
	int		scale;
	int		player_size;
	int		minimap_size;
	int		prefix_palyer_x;
	int		prefix_palyer_y;
	int		RayFacingDown;
	int		RayFacingUp;
	int		RayFacingRight;
	int		RayFacingLeft;
} t_map;

typedef struct s_player
{
	void	**images_walk;
	void	**images_shout;
	void	**images_Feeding;
	int		images_counter_walk;
	int		images_counter_shot;
	int		images_counter_Feeding;
	int		current_image;
	int		frame;
	int		is_state;
} t_player;

typedef struct s_game {
	t_config	*config;
	t_map		*map;
	int			start_parcing_map;
	int			player_x;
	int			player_y;
	float		player_pixl_x;
	float		player_pixl_y;

	int		is_door_hx;
	int		is_door_hy;
	int		is_door_vx;
	int		is_door_vy;
	float		dst_door_h;
	float		dst_door_v;


	int		is_door_x;
	int		is_door_y;
	float		dst_door;

	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	
	
	char	ray_valeu[WIDTH_3D];
	char	ray_valeu_v;
	char	ray_valeu_h;

	t_tex		img_north;
	t_tex		img_south;
	t_tex		img_east;
	t_tex		img_west;
	t_tex		img_door;

	int		is_open_door;
	float	distance_plane;
	float	wall_height;
	int		wall_top;
	int		wall_bottom;
	float	corrected_distance;
	
	char  		*addr;
	int			bits_per_pixel;
    int			line_length;
    int			endian;

	// 
	t_player *img_player;

} t_game;

typedef struct s_gnl
{
	char	*new_line;
	char	*return_line;
}	t_gnl;


# define BUFFER_SIZE		1
# define ERROR_ARG			"error to many argement"
# define NEED_ARG			"error i need path of map example : ./cub ./path/to/map.cub"
# define NAME_SHOURT		"error path is short"
# define ERROR_EXTENTION	"error in extension of file"
# define ERROR_ALOCATION	"error in alocation string"
# define NOT_FOUND			"error Icomplite texter"
# define ERROR_VALUE		"error inxpted value texter"
# define ERROR_KEY			"error inxpted KEY texter"
# define ERROR_DUP			"error duplicated or not found"
# define ERROR_MAP			"error invalide map"
# define ERROR_RENDER		"error in render game"
# define ERROR_IMG			"error in images game"

#define ERROR_WINDOW		"error in mlx_new_window"
#define ERROR_INIT			"error in mlx_init"
#define ERROR_IMAGE			"error in mlx_new_image"
#define ERROR_IMAGE_XPM	"error in mlx_xpm_file_to_image"

/****************************************
* 		Parsing function				*
*****************************************/

int		start_parcing(int argc, char *argv[], t_game *game);
int		filling_game(char *argv[], t_game *game);
int		init_struct(t_game *game);
int check_cloros(t_game *game, char *str);
int parce_and_filling_line(char **texter, char *str, int *index, char *prifex);
int check_diection_texter(t_game *game, char *str);
int filling_map(t_game *game, char *path);
int cheack_lines(t_game *game);

/****************************************
* 		Randering function				*
*****************************************/

int		start_randering(t_game *game);
int		create_window(t_game *game);
void	create_put_image_to_window(t_game *game);
void	ft_image(t_game *game, int width, int height);
int		create_xpm_file_image(t_game *game);
void	calculate_width_height(t_game *game);
int		moving(int key, t_game *game);
void    setup_player(t_game *game);
void    put_pixel(t_game *game, int x, int y, int color);
void	store_dir(t_game *game, int width, int height);
void	setup_ray(t_game *game);
void image_3d(t_game *game);
int create_image(t_game *game);
void setup1_ray(t_game *game);
float ray_cast(t_game *game, float ray_angle, int ray_count);

int move_player(t_game *game, float y, float x, int i);
void directoin_player(t_game *game);
float distance_palyer_wall(t_game *game, float dis_v, float dis_h, int ray_count);

/*
	bonus
*/

int mouse_move_player(int x, int y, void *struct_game);
int loading_image(t_game *game);
int loop_inimation(t_game *game);
void update_state(t_game *game);
void render_images(t_game *game);
void free_feed_images(t_game *game);
void free_shot_images(t_game *game);
void free_walk_images(t_game *game);
char *path_image_image(char *PRE_FIX, int n);

/****************************************
*			error						*
*****************************************/
void	ft_putendl_fd(char *s, int fd);

/****************************************
*			get next line				*
*****************************************/

char	*get_next_line(int fd);
char	*ft_strjoin_line(char *line, char *buff);
char	*ft_strchr_line(char *s, int c);
size_t	ft_strlen_line(char *s);
char	*extract_first_line(const char *line);
char	*update_remaining_line(char *line);
char	*ft_strdup_line(char *s);

/****************************************
*			utils						*
*****************************************/

int	ft_strlen(const char *s);
int	ft_strcmp(char *s1, char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_substr(char *str, int start, int end);
char	*ft_strchr(const char *s, int c);
char	*ft_other_strdup(char *s);
char	*ft_itoa(int n);
int	ft_isdigit(int c);
int	ft_mini_atoi(char *str, int start, int end);
void free_game(t_game *game);

/****************************************
*	ceiling_color = (game->config->ceiling_color[0] << 16) | 
					(game->config->ceiling_color[1] << 8) | 
					game->config->ceiling_color[2];
	floor_color = (game->config->floor_color[0] << 16) | 
				  (game->config->floor_color[1] << 8) | 
				  game->config->floor_color[2];				*
*****************************************/

#endif