NAME = cub3D


LIBFT	= libft/

LIBFTTARGET	= $(LIBFT)libft.a

SRC_DIR = src/

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

MLX42FLAGS = -Iinclude -lglfw -framework Cocoa -framework OpenGL -framework IOKit

HEADER_FILE = include/cub3d.h

RM = rm -f


SRCS =		$(SRC_DIR)main.c \
			$(SRC_DIR)init.c \
			$(SRC_DIR)init_2.c \
			$(SRC_DIR)error.c \
			$(SRC_DIR)raycasting.c \
			$(SRC_DIR)raycasting_utils.c \
			$(SRC_DIR)ray_algorithm.c \
			$(SRC_DIR)render.c \
			$(SRC_DIR)textures.c \
			$(SRC_DIR)weapon.c \
			$(SRC_DIR)map.c \
			$(SRC_DIR)map_validation.c \
			$(SRC_DIR)mini_map.c \


OBJS = $(SRCS:.c=.o)

%.o: %.c $(HEADER_FILE)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) 
	@$(MAKE) -C $(LIBFT)
	@$(CC) $(CFLAGS) $(MLX42FLAGS) $(OBJS) -o $(NAME) $(LIBFTTARGET) libmlx42.a 

all: $(NAME) 

clean:
	@$(MAKE) -C $(LIBFT) fclean
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
