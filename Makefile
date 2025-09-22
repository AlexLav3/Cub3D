NAME = cub3D
CC = cc -g 
OBJ_DIR = obj
#CFLAGS = -Wall -Werror -Wextra 

SOURCES = main.c init.c win_actions.c errors.c map.c utils.c
OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)/%.o)

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -lXext -lX11 -lm

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(MLX_LIB) $(MLX_FLAGS) $(LIBFT)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
