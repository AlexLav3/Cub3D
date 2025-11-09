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
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# define PI 3.14159265
# define TILE_SIZE 30
// if we decide not to set it as a constant but based on the map+window size
//tile_size can be put in a struct instead
# define PLAYER_HEIGHT 32
//I supposed it would be needed for the height part of the field of view
//#define FIELD_V 60 - 66 //for field of view once we decide

//find the X11 equivalent later (movement)
# define S 115
# define D 100
# define W 119
# define A 97

///textures (south, weast, east, north, floor, ceiling)
# define ST 1
# define WT 2
# define ET 3
# define NT 4
# define F 5
# define C 6

# define F_L 7 //first and last row of map, for the walls check
# define MID 8 //middle rows, also for walls check

typedef struct g_cub3D	t_cub3D;

typedef struct ray_cal
{
	//variables for ray casting calculations etc
}						t_ray_cal;

typedef struct g_player
{
	float				pos_x;
	float				pos_y;
	int					moving;
	int direction; //direction facing, may be not needed, idk.
	float				angle;
	//angle that the player is facing(?) to which apply the field of view
	float speed; //movement speed
}						t_player;

typedef struct g_map
{
	char				*file;

	//floor and ceiling colors based on config file
	int					f_red;
	int					f_green;
	int					f_blue;
	int					c_red;
	int					c_green;
	int					c_blue;

	//textures
	char				*N_text;
	char				*S_text;
	char				*E_text;
	char				*W_text;

	char *texture; //this one may be not necessary
	char *player;  //char that is equal to player initial position ("P")
	int					walkable;
	int count; //lines count
	char				**copy;
	int conf_c; //end of conf lines
	t_cub3D				*cub3D;
}						t_map;

//variables and pointers to struct needed for mlx
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
int						map_error(int fd);

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
char					*config_l(int fd);
int						walls_check(t_map *map);
int						iter_rows(t_map *map, int index, int iter,  bool middle);
//window actions
int						ft_key_press(int keycode, void *v);
int						ft_close(t_cub3D *cub3D);

//player actions
void					move_player(t_player *player, float x_factor,
							float y_factor);

#endif
