CC = cc

NAME = cub3D

FLAGS = -Wall -Wextra -Werror -g3
LIB_DIR = libft

LIBFT = $(LIB_DIR)/libft.a

SRC = 	src/parser/check_map.c  src/parser/parser.c  src/parser/read_file.c  src/parser/parse_map.c src/parser/parse_elements.c\
		src/tool/destroy.c src/tool/print_errors.c src/tool/tools.c \
		src/raycasting/graphic_2.c src/raycasting/graphic.c src/raycasting/init_ray.c src/raycasting/raycasting.c src/raycasting/textues.c\
		src/raycasting/textur_2.c\
		src/main.c

DIR = ./minilibx-linux

OBJ = $(SRC:%.c=%.o)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all : $(NAME)

$(LIBFT):
	make -C $(LIB_DIR)

$(NAME) : $(OBJ) $(LIBFT)
		$(CC) $(FLAGS) $(OBJ) $(LIBFT) -lm -L./minilibx-linux -lmlx -lX11 -lXext -o $@

clean :
	make -C $(LIB_DIR) clean
	rm -f $(OBJ)

fclean : clean
	make -C $(LIB_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re