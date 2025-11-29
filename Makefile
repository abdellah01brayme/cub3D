CC = cc

NAME = cub3D

FLAGS = -Wall -Wextra -Werror 
LIB_DIR = libft

LIBFT = $(LIB_DIR)/libft.a

SRC = 	parser/check_map.c  parser/parser.c  parser/read_file.c  parser/parse_map.c\
		src/main.c

DIR = ./minilibx-linux

OBJ = $(SRC:%.c=%.o)

all : $(NAME)

$(LIBFT):
	make -C $(LIB_DIR)

$(NAME) : $(OBJ) $(LIBFT)
		$(CC) $(FLAGS) $(OBJ) $(LIBFT) -L./minilibx-linux -lmlx -lX11 -lXext -o $@

clean :
	make -C $(LIB_DIR) clean
	rm -f $(OBJ)

fclean : clean
	make -C $(LIB_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re