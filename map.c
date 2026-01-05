/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 22:05:57 by elavrich          #+#    #+#             */
/*   Updated: 2026/01/06 00:09:55 by elavrich         ###   ########.fr       */
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

/*
sets the conf_end as y, for counting when the actual map starts
so we don't count configuration lines as part of the map size
Called inside init.c, and the conf_end value is used in walls_check, for example. 
Additionally, this sets the actual configurations, while config_l is used only for error checking
to avoid allocating an initializing things if configuration lines have wrong chars, or other errors.
*/
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
	map->conf_end = y;
}

void	create_copy(t_map *map)
{
	int	fd;
	int	y;
	int len;

	len = 0;
	y = 0;
	map->width = 0; //new, initialize width for mmap
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
			if(close(fd))	
				perror("close");
			return ;
		}
		len = ft_strlen(map->copy[y]);
		if (len > 0 && map->copy[y][len - 1] == '\n')
			len--;
		if (len > map->width)
			map->width = len;
		y++;
	}
	map->copy[y++] = NULL;
	if(close(fd))	
		perror("close");
}

int	walls_check(t_map *map)
{
	int	rows;
	int	middle;

	rows = map->conf_end;
	if (!iter_rows(map, rows, 0, false))
		return (0);
	while (map->copy[rows])
		rows++;
	if (!iter_rows(map, rows - 1, 0, false))
		return (0);
	middle = map->conf_end + 1;
	while (middle < rows - 1)
	{
		if (!iter_rows(map, middle, 0, true))
			return (0);
		middle++;
	}
	return (1);
}
