#ifndef CUB3D
# define CUB3D

# include "libft/get_next_line/get_next_line.h"
# include "libft/printf/ft_printf.h"
# include "libft/src/libft.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define PI 3.14159265
# define TILE_SIZE 64
# define PLAYER_HEIGHT 32

//find the X11 equivalent later
# define S 115
# define D 100
# define W 119
# define A 97

# define ST 1
# define WT 2
# define ET 3
# define NT 4
# define F 5
# define C 6

typedef struct g_cub3D	t_cub3D;

typedef struct g_player
{
	float				pos_x;
	float				pos_y;
	int					moving;
	int					direction;
	float				angle;
	float				speed;
}						t_player;

typedef struct g_map
{
	char				*file;

	int					f_red;
	int					f_green;
	int					f_blue;
	int					c_red;
	int					c_green;
	int					c_blue;

	char				*N_text;
	char				*S_text;
	char				*E_text;
	char				*W_text;

	char				*texture;
	char				*player;
	int					walkable;
	int					count;
	char				**copy;
	t_cub3D				*cub3D;
}						t_map;

typedef struct g_cub3D
{
	void				*mlx;
	void				*win;
	int					w_height;
	int					w_width;
	t_map				*map;
	t_player			*player;

}						t_cub3D;

//mlx_new_image(mlx, 128, 128);
//error handling
int						arg_error(int argc, char **argv);
int						map_error(char *argv, int fd);

//initializing & starting values
int						mlx_set(t_cub3D *Cub3D);
int						init_player(t_cub3D *Cub3D);
void					extract_color(char *line, int *colors);

//map
int						load_map(t_map *map);
void					set_textures_col(t_map *map, int op, char *path);
void					create_copy(t_map *map);
int						is_config_line(char *line);
void					set_colors(t_map *map, int op, char *line);
void					configs(t_map *map);
//window actions
int						ft_key_press(int keycode, void *v);
int						ft_close(t_cub3D *cub3D);

//player actions
void					move_player(t_player *player, float x_factor,
							float y_factor);

#endif
