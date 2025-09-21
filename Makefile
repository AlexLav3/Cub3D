NAME = cub3D
CC = cc -g 
#CFLAGS = -Wall -Werror -Wextra 

SOURCES = main.c
OBJECTS = $(SOURCES:.c=.o)

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -lXext -lX11 -lm

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(MLX_LIB) $(MLX_FLAGS) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
