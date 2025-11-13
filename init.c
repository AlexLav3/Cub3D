/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:24:35 by elavrich          #+#    #+#             */
/*   Updated: 2025/11/13 20:32:37 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	load_map(t_map *map)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open(map->file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	if(close(fd))
		  perror("close");
	map->count = count;
	map->copy = malloc((count + 1) * sizeof(char *));
	if (!map->copy)
		return (0);
	create_copy(map);
	return (1);
}
void	init_player_direction(t_cub3D *cub3D)
{
	t_player	*p;

	p = cub3D->player;
	if (p->dir == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	else if (p->dir == 'S')
	{
		p->dir_x = 0;
		p->dir_y = 1;
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
	else if (p->dir == 'E')
	{
		p->dir_x = 1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
	else if (p->dir == 'W')
	{
		p->dir_x = -1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
}

int	init_player(t_cub3D *cub3D)
{
	int	x;
	int	y;

	y = 0;
	while (cub3D->map->copy[y])
	{
		x = 0;
		while (cub3D->map->copy[y][x])
		{
			if (cub3D->map->copy[y][x] == 'N' ||
				cub3D->map->copy[y][x] == 'S' ||
				cub3D->map->copy[y][x] == 'E' ||
				cub3D->map->copy[y][x] == 'W')
			{
				cub3D->player->dir = cub3D->map->copy[y][x];
				cub3D->player->pos_x = (float)x + 0.5;
				cub3D->player->pos_y = (float)y + 0.5;
				cub3D->map->copy[y][x] = '0';
				init_player_direction(cub3D);
				if (DEBUG_INIT)
				{
					printf("Player spawned at: (%.2f, %.2f)\n", 
						cub3D->player->pos_x, cub3D->player->pos_y);
					printf("Direction vector: (%.2f, %.2f)\n",
						cub3D->player->dir_x, cub3D->player->dir_y);
					printf("Map dimensions: %d lines\n", cub3D->map->count - cub3D->map->conf_c); //added -cub3D->map->conf_c

				}
				return (1);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	mlx_set(t_cub3D *Cub3D)
{
	Cub3D->win = mlx_new_window(Cub3D->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!Cub3D->win)
		return (0);
	Cub3D->img.img = mlx_new_image(Cub3D->mlx, WIN_WIDTH, WIN_HEIGHT); //what is this for? there is no image (aside textures)
	if (!Cub3D->img.img)
		return (0);
	Cub3D->img.addr = mlx_get_data_addr(Cub3D->img.img,
		&Cub3D->img.bits_per_pixel,
		&Cub3D->img.line_len,
		&Cub3D->img.endian);
	configs(Cub3D->map);
	if(!walls_check(Cub3D->map))
		return (printf("Not enclosed by walls\n"), 0);
	if (!init_player(Cub3D))
		return (0);
	render_3d_view(Cub3D);
	debug_player_spawn_simple(Cub3D);
	debug_print_map_raw(Cub3D->map);
	mlx_hook(Cub3D->win, 17, 0, ft_close, (void *)Cub3D);
	mlx_hook(Cub3D->win, 2, 1L << 0, ft_key_press, (void *)Cub3D);
	mlx_hook(Cub3D->win, 3, 1L << 1, ft_key_release, (void *)Cub3D);
	mlx_loop(Cub3D->mlx);
	return (1);
}

void	set_textures_col(t_map *map, int op, char *path)
{
	int		width;
	int		height;
	int		len;
	t_cub_img	*texture;

	width = 64;
	height = 64;
	len = ft_strlen(path);
	
	// Trim whitespace
	while (len > 0 && (path[len - 1] == '\n' || path[len - 1] == ' ' || 
			path[len - 1] == '\t'))
		path[--len] = '\0';
	// Select which texture to load
	if (op == NT)
		texture = &map->N_text;
	else if (op == ST)
		texture = &map->S_text;
	else if (op == ET)
		texture = &map->E_text;
	else if (op == WT)
		texture = &map->W_text;
	else
		return;
	
	texture->img = mlx_xpm_file_to_image(map->cub3D->mlx, path, &width, &height);
	if (!texture->img)
	{
		printf("Error: failed to load texture from '%s'\n", path);
		return;
	}
	if (texture->img)
	{
		// Get the data address for direct pixel access
		texture->addr = mlx_get_data_addr(texture->img, 
			&texture->bits_per_pixel,
			&texture->line_len, 
			&texture->endian);
	}
}

void	set_colors(t_map *map, int op, char *line)
{
	int	colors[3];
	
	extract_color(line, colors);
	if (op == F)
	{
		map->f_red = colors[0];
		map->f_green = colors[1];
		map->f_blue = colors[2];
	}
	else if (op == C)
	{
		map->c_red = colors[0];
		map->c_green = colors[1];
		map->c_blue = colors[2];
	}
}
