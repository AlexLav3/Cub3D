/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 22:05:57 by elavrich          #+#    #+#             */
/*   Updated: 2025/11/09 23:41:41 by elavrich         ###   ########.fr       */
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
			if(close(fd))	
				perror("close");
			return ;
		}
		y++;
	}
	map->copy[y] = NULL;
	if(close(fd))	
		perror("close");
}

//this can be easily separated, first two loops are identical. 
int walls_check(t_map *map)
{
	int rows = map->conf_c;
	int i = 0;
	while(map->copy[rows][i] == ' ') //skip initial spaces if any
		i++;
	while(map->copy[rows][i] != '\n') //first row
	{
		if(map->copy[rows][i] != '1')	
			return 0;
		i++;
	}
	i = 0;
	while(map->copy[rows]) //find the boundary
		rows++;
	int last_row = rows -1;
	while(map->copy[last_row][i]) //last row
	{
		while(map->copy[last_row][i] == ' ')
			i++;
		if(map->copy[last_row][i] != '1')	
			return 0;
		i++;
	}
	int middle = map->conf_c + 1;
	i = 0;
	while(middle < last_row)
	{
		while(map->copy[middle][i] == ' ')
    		i++;
		if(map->copy[middle][i] != '1')
			return 0;
		int j = ft_strlen(map->copy[middle]) - 1;
		while(map->copy[middle][j] == ' ' || map->copy[middle][j] == '\n')
    		j--;
		if(map->copy[middle][j] != '1')
    		return 0;
		i = 0;
		middle++;		
	}
	return 1;
}
