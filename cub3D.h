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

typedef struct g_player
{
	int			pos_x;
	int			pos_y;
	int			moving;
	int			direction;

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

#endif
