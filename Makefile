CC = cc
CFLAG =   -Wall -Wextra -Werror #-g -fsanitize=address

SRC_MAIN = \
	./main.c

SRC_PARCING = \
	./Parsing/check_args.c \
	./Parsing/filling_game.c \
	./Parsing/init_struct.c \
	./Parsing/parcing_color.c \
	./Parsing/parcing_dir.c \
	./Parsing/parcing_map.c \
	./Parsing/cheack_lines.c \
	./Parsing/check_door.c

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
	./utils/ft_isdigit.c \
	./utils/ft_mini_atoi.c \
	./utils/ft_memcpy.c

SRC_RANDER = \
	./rander/stup_minimap_player.c \
	./rander/start_randering.c \
	./rander/rollback.c \
	./rander/ray_drawing.c \
	./rander/ray_casting.c \
	./rander/move.c \
	./rander/move_palyer.c \
	./rander/loading_image.c \
	./rander/init_image_player.c \
	./rander/handel_direction.c \
	./rander/get_vertical.c \
	./rander/get_horizontal.c \
	./rander/drow_texter.c \
	./rander/algo_door.c


OBJ = $(SRC_RANDER:.c=.o) $(SRC_PARCING:.c=.o) $(SRC_MAIN:.c=.o) $(SRC_ERROR:.c=.o) $(SRC_GET_LINE:.c=.o) $(SRC_UTILS:.c=.o)

HEADER = cub.h

NAME = cub3D

MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit -lm

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAG) $(OBJ) $(MLX_FLAGS)  -o $(NAME) 

%.o : %.c $(HEADER)
	$(CC) $(CFLAG) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
