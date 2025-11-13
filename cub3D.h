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
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define PI 3.14159265
# define TILE_SIZE 30
# define PLAYER_HEIGHT 32

//Minimap vars
# define MMAP_PIXEL_SIZE 128
# define MMAP_VIEW_DIST 4
# define MMAP_COLOR_PLAYER 0x00FF00
# define MMAP_COLOR_WALL 0x808080
# define MMAP_COLOR_FLOOR 0xE6E6E6
# define MMAP_COLOR_SPACE 0x404040

# define MOVESPEED 0.1
# define ROTSPEED 0.05

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

# define F_L 7 //first and last row of map, for the walls check
# define MID 8 //middle rows, also for walls check

# define WIN_WIDTH 800  // Width of the game window
# define WIN_HEIGHT 600 // Height of the game window
# define FOV 0.66       // Field of view (radians) - Alex: fyi I tried to change it and there was no difference whatsoever. 
# define RAY_STEP 0.01  // How much we advance the ray each iteration
# define MAX_DEPTH 20.0 // Maximum distance a ray can travel

# define DEBUG_MODE 1
# define DEBUG_MOVEMENT 1
# define DEBUG_ROTATION 1
# define DEBUG_RENDER 1
# define DEBUG_MINIMAP 1
# define DEBUG_INIT 1
# define DEBUG_INPUT 1

typedef struct g_cub3D	t_cub3D;

typedef struct s_cub_img
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_len;
	int					endian;
}						t_cub_img;

typedef struct s_minimap
{
	char				**map;
	t_cub_img			img;
	int					size;
	int					offset_x;
	int					offset_y;
	int					view_dist;
	int					tile_size;
}						t_minimap;

typedef struct s_color
{
	int r; // Red component (0-255)
	int g; // Green component (0-255)
	int b; // Blue component (0-255)
}						t_color;

typedef struct s_ray
{
	float angle;      // Direction angle of the ray
	float distance;   // Distance to wall hit
	int hit_vertical; // Did we hit a vertical wall? (for coloring)
	float wall_x;     // X coordinate where ray hit the wall
	float wall_y;     // Y coordinate where ray hit the wall
}						t_ray;

typedef struct g_player
{
	float pos_x;   // Player X position
	float pos_y;   // Player Y position
	float dir_x;   // Direction vector X
	float dir_y;   // Direction vector Y
	float plane_x; // Camera plane X
	float plane_y; // Camera plane Y
	char dir;      // Initial direction (N/S/E/W)
	int move_x;    // Strafe movement (-1, 0, 1)
	int move_y;    // Forward/back movement (-1, 0, 1)
	int rotate;    // Rotation (-1, 0, 1)
	int has_moved; // Movement flag
	float angle;   // Player angle (might not need this if using dir_x/dir_y)
	float speed;   // Movement speed
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
	t_cub_img			N_text;
	t_cub_img			S_text;
	t_cub_img			E_text;
	t_cub_img			W_text;
	char				*texture;
	char				*player;
	int					walkable;
	int					count;
	int					width;
	char				**copy;
	int					conf_c;
	t_cub3D				*cub3D;
}						t_map;

typedef struct g_cub3D
{
	void				*mlx;
	void				*win;
	int					w_height;
	t_cub_img img; //drawing buffer
	int					w_width;
	t_map				*map;
	t_player			*player;

}						t_cub3D;

//error handling
int						arg_error(int argc, char **argv);
int						map_error(int fd);

//initializing & starting values
int						mlx_set(t_cub3D *Cub3D);
int						init_player(t_cub3D *Cub3D);
void					extract_color(char *line, int *colors);
void					render_3d_view(t_cub3D *cub3D);
int						create_rgb(int r, int g, int b);

//map
int						load_map(t_map *map);
void					set_textures_col(t_map *map, int op, char *path);
void					create_copy(t_map *map);
int						is_config_line(char *line);
void					set_colors(t_map *map, int op, char *line);
void					configs(t_map *map);
int						is_wall(t_map *map, int x, int y);
float					normalize_angle(float angle);
t_ray					cast_single_ray(t_player *player, t_map *map,
							float ray_angle);
int						calculate_wall_height(float distance);
int						get_wall_color(t_ray ray);
void					draw_vertical_line(t_cub3D *cub3D, int x,
							int wall_height, int color);
void					my_mlx_pixel_put(t_cub_img *img, int x, int y,
							int color);
t_cub_img				*get_wall_texture(t_map *map, t_ray ray);
void					render_minimap(t_cub3D *cub3D);
int						walls_check(t_map *map);

//minimap_1.c
int						get_minimap_offset(t_minimap *minimap, int mapsize,
							int pos);
int						is_valid_map_coord(int coord, int size);
char					*add_minimap_line(t_cub3D *cub3D, t_minimap *m, int y);
char					**generate_minimap(t_cub3D *cub3D, t_minimap *minimap);
void					draw_minimap_ray(t_minimap *m, t_player *p);

//minimap_2.c
void					set_minimap_tile_pixels(t_minimap *m, int x, int y,
							int color);
void					draw_minimap_tile(t_minimap *minimap, int x, int y);
void					set_minimap_border(t_minimap *minimap, int color);
void					debug_display_minimap(t_minimap *minimap);

//window actions
int						ft_key_press(int keycode, void *v);
int						ft_close(void *param);
int						ft_key_release(int keycode, void *v);
//player actions
int						validate_move(t_cub3D *cub3D, float new_x, float new_y);
int						move_player(t_cub3D *cub3D);
int						rotate_player(t_cub3D *cub3D, float rotdir);

//debug
void					debug_player_state(t_cub3D *cub3D, const char *context);
void					debug_movement(t_cub3D *cub3D, const char *direction);
void					debug_rotation(t_cub3D *cub3D, float rotdir);
void					debug_init_complete(t_cub3D *cub3D);
void					debug_map_info(t_map *map);
void					debug_key_press(int keycode);
void					debug_key_release(int keycode);
void					debug_render_frame(int frame_count);

//int						game_loop(void *param); //unused - see comment on function
char					*config_l(int fd);
int						iter_rows(t_map *map, int index, int iter, bool middle);
void					debug_print_map_raw(t_map *map);
char					get_map_char(t_map *map, int x, int y);
void					debug_player_spawn_simple(t_cub3D *cub3D);

#endif