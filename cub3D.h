/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 22:07:14 by jcouto            #+#    #+#             */
/*   Updated: 2026/01/24 01:04:14 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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

# define MOVESPEED 0.1
# define ROTSPEED 0.05

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

# define F_L 7
# define MID 8

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define FOV 0.66
# define RAY_STEP 0.01
# define MAX_DEPTH 20.0

typedef struct g_cub3	t_cub3;

typedef struct s_cub_img
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_len;
	int					endian;
}						t_cub_img;

typedef struct s_color
{
	int					r;
	int					g;
	int					b;
}						t_color;

typedef struct s_rgb
{
	int					red;
	int					green;
	int					blue;
}						t_rgb;

typedef struct s_ray
{
	float				angle;
	float				distance;
	int					hit_vertical;
	float				wall_x;
	float				wall_y;
}						t_ray;

typedef struct s_dir_init
{
	char				dir;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
}						t_dir_init;

typedef struct g_player
{
	float				pos_x;
	float				pos_y;
	float				dir_x;
	float				dir_y;
	float				plane_x;
	float				plane_y;
	char				dir;
	int					move_x;
	int					move_y;
	int					rotate;
	int					has_moved;
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
	t_cub_img			n_text;
	t_cub_img			s_text;
	t_cub_img			e_text;
	t_cub_img			w_text;
	char				*texture;
	char				*player;
	int					walkable;
	int					count;
	int					width;
	char				**copy;
	int					conf_end;
	t_cub3				*cub3;
}						t_map;

typedef struct s_texture_params
{
	int					y;
	int					start_y;
	int					end_y;
	int					tex_x;
	int					tex_y;
	float				tex_y_step;
	float				tex_y_pos;
	t_cub_img			*texture;
	int					color;
}						t_texture_params;

typedef struct g_cub3
{
	void				*mlx;
	void				*win;
	int					w_height;
	t_cub_img			img;
	t_texture_params	*tmp;
	int					w_width;
	t_map				*map;
	t_player			*player;

	float				player_angle;
	float				angle_diff;
	int					wall_height;
	float				perpendicular_distance;
	int					x;
	float				camera_x;
	float				ray_dir_x;
	float				ray_dir_y;
	float				ray_angle;
}						t_cub3;

typedef struct s_ray_state
{
	float				x;
	float				y;
	float				dir_x;
	float				dir_y;
	float				distance;
	int					prev_map_x;
}						t_ray_state;

static const t_dir_init	g_dirs[] = {
	{'N', 0, -1, 0.66, 0},
	{'S', 0, 1, -0.66, 0},
	{'E', 1, 0, 0, 0.66},
	{'W', -1, 0, 0, -0.66},
};

// errors.c - Error handling and validation
bool					arg_error(int argc, char **argv);
bool					map_error(int fd);
int						is_config_line(char *line);

int						main(int argc, char **argv);

// init.c - Initialization functions
bool					mlx_set(t_cub3 *cub3);
bool					init_player(t_cub3 *cub3);
void					init_player_direction(t_cub3 *cub3);
void					set_colors(t_map *map, int op, char *line);

// init_utils.c - Player initialization utilities
bool					player_found(t_cub3 *cub3, int actual_y, int x, int y);
void					player_var(t_cub3 *cub3, int y, int x, int a_y);
void					set_text_add(t_cub_img *texture);
bool					set_textures_col(t_map *map, int op, char *path);

// map.c - Map loading and configuration
bool					load_map(t_map *map);
void					create_copy(t_map *map);
int						configs(t_map *map);
bool					walls_check(t_map *map);

// map_utils.c - Map utility functions
int						is_wall(t_map *map, int x, int y);
char					get_map_char(t_map *map, int x, int y);

// utils.c - General utilities
void					extract_color(char *line, int *colors);
char					*config_l(int fd);
bool					iter_rows(t_map *map, int index, int iter, bool middle);
void					set_texts_w(t_cub3 *cub3, int wall_height, t_ray ray);

// raycast.c - Core raycasting algorithm
t_ray					cast_single_ray(t_player *player, t_map *map,
							float ray_angle);

// raycast_utils.c - Raycasting utilities
void					draw_vertical_line(t_cub3 *cub3, int x, int wall_height,
							int color);

// colors.c - Color manipulation functions
int						create_rgb(int r, int g, int b);
int						get_wall_color(t_ray ray);

// render.c - Main rendering functions
void					render_3d_view(t_cub3 *cub3, int x);
int						get_texture_color(t_cub_img *texture, int tex_x,
							int tex_y);
t_cub_img				*get_wall_texture(t_map *map, t_ray ray);
int						calculate_texture_x(t_ray ray);
void					draw_textured_wall(t_cub3 *cub3, int x, int wall_height,
							t_ray ray);

// render_utils.c - Rendering utilities
void					put_walls_ceiling(t_cub3 *cub3, int y, int x,
							int draw_end);
int						calculate_wall_height(float distance);
float					normalize_angle(float angle);
void					my_mlx_pixel_put(t_cub_img *img, int x, int y,
							int color);

// win_actions.c - Window and input handling
int						ft_key_press(int keycode, void *v);
int						ft_close(void *param);
int						ft_key_release(int keycode, void *v);

// p_movement_1.c - Player movement
bool					validate_move(t_cub3 *cub3, float new_x, float new_y);
int						move_player(t_cub3 *cub3);
int						rotate_player(t_cub3 *cub3, float rotdir);

// clean.c - Cleanup and memory management
void					clean_imgs(t_cub3 *cub3);
void					map_errfree(char **map, int fd, int y);

#endif