CC = cc
CFLAG = -fsanitize=address -g #-Wall -Wextra -Werror

SRC_MAIN = \
	./main.c

SRC_PARCING = \
	./Parsing/check_args.c \
	./Parsing/filling_game.c \
	./Parsing/init_struct.c \
	./Parsing/parcing_color.c \
	./Parsing/parcing_dir.c \
	./Parsing/parcing_map.c \
	./Parsing/cheack_lines.c

SRC_ERROR = \
	./error/print_error.c

SRC_GET_LINE = \
	./get_next_line/get_next_line_utils.c \
	./get_next_line/get_next_line.c

SRC_UTILS = \
	./utils/ft_strlen.c \
	./utils/ft_strcmp.c \
	./utils/ft_strncmp.c \
	./utils/ft_substr.c \
	./utils/ft_strchr.c \
	./utils/ft_other_strdup.c \
	./utils/free_game.c \
	./utils/ft_itoa.c \
	./utils/ft_isdigit.c

SRC_RANDER = \
	./rander/file_create_window.c \
	./rander/move_player.c \
	./rander/ray_casting.c \
	./rander/ray_drawing.c \
	./rander/handel_direction.c \
	./rander/start_randering.c \
	./rander/loading_image.c \
	./utils/ft_mini_atoi.c


OBJ = $(SRC_RANDER:.c=.o) $(SRC_PARCING:.c=.o) $(SRC_MAIN:.c=.o) $(SRC_ERROR:.c=.o) $(SRC_GET_LINE:.c=.o) $(SRC_UTILS:.c=.o)

HEADER = cub.h

NAME = cub

# MLX_DIR = ./minilibx-mac

MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit -lm
all : $(NAME) clean
	clear
	./cub ./texter/map.cub

$(NAME) : $(OBJ)
	$(CC) $(CFLAG) $(MLX_FLAGS) $(OBJ) -o $(NAME) 
#$(MAKE) -C $(MLX_DIR)
#$(MLX_FLAGS)

%.o : %.c $(HEADER)
	$(CC) $(CFLAG) -c $< -o $@

clean :
	rm -f $(OBJ)
# $(MAKE) -C $(MLX_DIR) clean

fclean : clean
	rm -f $(NAME)
# $(MAKE) -C $(MLX_DIR) clean

re : fclean all

.PHONY: all clean fclean re
