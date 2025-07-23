/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:10:35 by hkhairi           #+#    #+#             */
/*   Updated: 2025/07/02 18:32:14 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB_H
# define CUB_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <limits.h>
# include <fcntl.h>


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
	char **grid;
	int width;
	int height;
} t_map;

typedef struct s_game {
	t_config *config;
	t_map *map;
	int start_parcing_map;
	int player_x;
	int player_y;
	char player_dir;
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