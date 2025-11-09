/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 22:05:57 by elavrich          #+#    #+#             */
/*   Updated: 2025/11/10 00:18:13 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// NO ./path_to_the_north_texture
// SO ./path_to_the_south_texture
// WE ./path_to_the_west_texture
// EA ./path_to_the_east_texture

//rgb(red, green, blue)
// F 220,100,0
// C 225,30,0

//floor & ceiling have color

//check configs and parse accordingly
//if configs missing -> error

//check map
//display textures as needed

static int	set_config(t_map *map, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		set_textures_col(map, NT, line + 3);
	else if (!ft_strncmp(line, "SO ", 3))
		set_textures_col(map, ST, line + 3);
	else if (!ft_strncmp(line, "WE ", 3))
		set_textures_col(map, WT, line + 3);
	else if (!ft_strncmp(line, "EA ", 3))
		set_textures_col(map, ET, line + 3);
	else if (!ft_strncmp(line, "F ", 2))
		set_colors(map, F, line + 2);
	else if (!ft_strncmp(line, "C ", 2))
		set_colors(map, C, line + 2);
	return (1);
}

void	configs(t_map *map)
{
	int	y;

	y = 0;
	while (map->copy[y][0])
	{
		if (is_config_line(map->copy[y]) || map->copy[y][0] == '\n')
		{
			set_config(map, map->copy[y]);
			y++;
		}
		else
			break ;
	}
	map->conf_c = y;
}

void	create_copy(t_map *map)
{
	int	fd;
	int	y;

	y = 0;
	fd = open(map->file, O_RDONLY);
	if (fd < 0)
		return (free(map->copy));
	while (y < map->count)
	{
		map->copy[y] = get_next_line(fd);
		if (!map->copy[y])
		{
			while (--y >= 0)
				free(map->copy[y]);
			free(map->copy);
			map->copy = NULL;
			if (close(fd))
				perror("close");
			return ;
		}
		y++;
	}
	map->copy[y] = NULL;
	if (close(fd))
		perror("close");
}

int	walls_check(t_map *map)
{
	int	rows;
	int	middle;
	int	j;

	rows = map->conf_c;
	if (!iter_rows(map, rows, 0, false))
		return (0);
	while (map->copy[rows])
		rows++;
	if (!iter_rows(map, rows - 1, 0, false))
		return (0);
	middle = map->conf_c + 1;
	while (middle < rows - 1)
	{
		if (!iter_rows(map, middle, 0, true))
			return (0);
		middle++;
	}
	return (1);
}
