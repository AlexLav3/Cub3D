/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:24:35 by elavrich          #+#    #+#             */
/*   Updated: 2025/09/26 23:06:32 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	test(t_map *map)
{
	mlx_put_image_to_window(map->cub3D->mlx, map->cub3D->win, map->N_text, 2
			* TILE_SIZE, 2 * TILE_SIZE);
	printf("colors: %d, %d, %d\n", map->c_red, map->c_green, map->c_blue);
}

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
		exit(EXIT_FAILURE);
	map->count = count;
	map->copy = malloc((count + 1) * sizeof(char *));
	if (!map->copy)
		return (0);
	create_copy(map);
	return (1);
}

int	init_player(t_cub3D *cub3D)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (cub3D->map->copy[y])
	{
		x = 0;
		while (cub3D->map->copy[y][x])
		{
			if (cub3D->map->copy[y][x] == 'N')
			{
				cub3D->map->copy[y][x] = '0';
				cub3D->player->pos_x = x;
				cub3D->player->pos_y = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	mlx_set(t_cub3D *Cub3D)
{
	Cub3D->win = mlx_new_window(Cub3D->mlx, 200, 200, "cub3D"); //tmp win size
	if (!Cub3D->win)
		return (0);
	configs(Cub3D->map);
	test(Cub3D->map);
	mlx_hook(Cub3D->win, 17, 0, ft_close, (void *)Cub3D);
	mlx_hook(Cub3D->win, 2, 1L << 0, ft_key_press, (void *)Cub3D);
	mlx_loop(Cub3D->mlx);
	return (1);
}

void	set_textures_col(t_map *map, int op, char *path)
{
	int	a;
	int	len;

	a = 200;
	len = ft_strlen(path);
	while (len > 0 && (path[len - 1] == '\n' || path[len - 1] == ' ' || path[len
			- 1] == '\t'))
		path[--len] = '\0';
	if (op == NT)
		map->N_text = mlx_xpm_file_to_image(map->cub3D->mlx, path, &a, &a);
	else if (op == ST)
		map->S_text = mlx_xpm_file_to_image(map->cub3D->mlx, path, &a, &a);
	else if (op == ET)
		map->E_text = mlx_xpm_file_to_image(map->cub3D->mlx, path, &a, &a);
	else if (op == WT)
		map->W_text = mlx_xpm_file_to_image(map->cub3D->mlx, path, &a, &a);
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

