/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:10:35 by hkhairi           #+#    #+#             */
/*   Updated: 2025/08/14 11:25:43 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB_H
# define CUB_H

# include <mlx.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <limits.h>
# include <fcntl.h>
# include <math.h>

# define SIZE 32
# define FOV 60 * M_PI / 180 // = 60
# define ESC 53
# define WIDTH_IM 1280
# define HEIGHT_IM 768
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define NUM_GAME_MOVES 8

// # define ANGLE 0.5







typedef struct s_config {
	char *no_texture;
	char *so_texture;
	char *we_texture;
	char *ea_texture;
	int *check_duplicate;
	int floor_color[3];
	int ceiling_color[3];
} t_config;

typedef struct s_map {
	char	**grid;
	float	dis[WIDTH_IM];
	float	angle;
	char	palyer;
	float	Yh_vertical;
	float	Xh_vertical;
	float	Yh_horizontal;
	float	Xh_horizontal;
	float	d_X;
	float	d_Y;
	int		width_angel;
	int		width;
	int		height;
} t_map;

typedef struct s_game {
	t_config	*config;
	t_map		*map;
	int			start_parcing_map;
	int			player_x;
	int			player_y;
	float		player_pixl_x;
	float		player_pixl_y;
	char		player_dir;

	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	
	
	void		*img_p;
	char  		*addr;
	char  		*addr1;
	int			bits_per_pixel;
    int			line_length;
    int			endian;

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

/****************************************
* 		Parsing function				*
*****************************************/

int		start_parcing(int argc, char *argv[], t_game *game);
int		filling_game(int argc, char *argv[], t_game *game);
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
void	Calculate_width_height(t_game *game);
int		moving(int key, t_game *game);
void    setup_player(t_game *game);
void    put_pixel(t_game *game, int x, int y, int color);
void	store_dir(t_game *game, int width, int height);
void	setup_ray(t_game *game);
void image_3D(t_game *game);

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

#endif