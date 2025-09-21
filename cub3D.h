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

typedef struct g_player
{
	float		pos_x;
	float		pos_y;
	int			moving;
	int			direction;
	float       angle;
    float       speed;
}				t_player;

typedef struct g_map
{
	char		*file;
	char		*floor;
	char		*wall;
	char		*texture;
	char		*player;
	int			walkable;

}				t_map;

typedef struct g_cub3D
{
	void		*mlx;
	void		*win;
	int			w_height;
	int			w_width;
	t_map		*map;
	t_player	*player;

}				t_cub3D;

//error handling
int				arg_error(int argc, char **argv);
int				map_error(char *argv, int fd);

//initializing & starting values
int				mlx_set(t_cub3D *Cub3D);
int				init_player(t_player *player);

//window actions
int				ft_key_press(int keycode, void *v);
int				ft_close(t_cub3D *cub3D);

//player actions
void	move_player(t_player *player, float x_factor, float y_factor);


#endif
