/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:24:35 by elavrich          #+#    #+#             */
/*   Updated: 2025/09/22 17:39:46 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void test(t_map *map)
{
	printf("hi?\n");
	mlx_put_image_to_window(map->cub3D->mlx, map->cub3D->win, map->N_text, 2 * TILE_SIZE,  2 * TILE_SIZE);
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
	close(fd);
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
	a = 200;
	printf("%s\n", path);
	if(!path)
		return;
	if (op == NT)
		map->N_text = mlx_xpm_file_to_image(map->cub3D->mlx, path, &a, &a); //why this yes, but path no? (path = ./textures/North.xpm)
	else if (op == ST)
		map->S_text = mlx_xpm_file_to_image(map->cub3D->mlx, path, &a, &a);
	else if (op == ET)
		map->E_text = mlx_xpm_file_to_image(map->cub3D->mlx, path, &a, &a);
	else if (op == WT)
		map->W_text = mlx_xpm_file_to_image(map->cub3D->mlx, path, &a, &a);
}

void	set_colors(t_map *map, int op, char *line)
{
	int	num;

	num = 0;
	while (*line)
	{
		if (*line == ',')
			break ;
		if (*line >= '0' && *line <= '9')
			num = num * 10 + *line - '0';
		line++;
	}
	if (op == F)
	{
		if (!map->f_red)
			map->f_red = num;
		if (*line + 1 != '\0')
		{
			set_colors(map, op, line + 1);
			if (!map->f_green)
				map->f_green = num;
			if (!map->f_blue)
				map->f_blue = num;
			else
				return ;
		}
	}
	if (op == C)
	{
		if (!map->c_red)
			map->c_red = num;
		if (*line + 1 != '\0')
		{
			set_colors(map, op, line + 1);
			if (!map->c_green)
				map->c_green = num;
			if (!map->c_blue)
				map->c_blue = num;
			else
				return ;
		}
	}
}
