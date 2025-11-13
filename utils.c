/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:52:05 by elavrich          #+#    #+#             */
/*   Updated: 2025/11/13 19:35:55 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		extract_color(char *line, int *colors)
{
	int	i;
	int	count;
	int	val;

	i = 0;
	count = 0;
	val = 0;
	while (line[i] && count < 3)
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		val = 0;
		while (line[i] >= '0' && line[i] <= '9')
		{
			val = val * 10 + (line[i] - '0');
			i++;
		}
		colors[count++] = val;
		if (line[i] == ',')
		{
			i++;
		}
	}
}

/*
this is for error checking before we even create the copy
To avoid allocating the copy if there is any issue.
This function is called by map_error. (errors.c) 
*/
char	*config_l(int fd)
{
	char	*line;

	while ((line = get_next_line(fd)))
	{
		if (is_config_line(line) || line[0] == '\n')
			free(line);
		else
		{
			free(line);
			break ;
		}
	}
	return (line);
}

//function unused for now
// void sizem(t_cub3D *Cub3D) //size of map
// {
// 	int rows = Cub3D->map->conf_c;
// 	int columns = 0;
// 	while (Cub3D->map->copy[rows] != NULL)
// 		rows++;
// 	if (rows > 0)
// 		columns = ft_strlen(Cub3D->map->copy[Cub3D->map->conf_c]) - 1;
// 	else
// 		columns = 0;
// 	Cub3D->w_height = rows * TILE_SIZE;
// 	Cub3D->w_width = columns * TILE_SIZE;
// }
// as we allow jagged edges,this will need to be changed,if we need the function.

int	iter_rows(t_map *map, int index, int iter, bool middle)
{
	int	j;

	if (!middle)
	{
		while (map->copy[index][iter] == ' ')
			iter++;
		while (map->copy[index][iter] != '\n' && map->copy[index][iter] != '\0')
		{
			if (map->copy[index][iter] != '1' && map->copy[index][iter] != ' ') //only 1 and spaces are allowed in the first and last row
				return (0);
			iter++;
		}
		return (1);
	}
	while (map->copy[index][iter] == ' ') //skip spaces
		iter++;
	if (map->copy[index][iter] != '1') //first wall of middle rows
		return (0);
	j = ft_strlen(map->copy[index]) - 1; //find end of row
	while (map->copy[index][j] == ' ' || map->copy[index][j] == '\n') //skip spaces or newlines
		j--;
	if (map->copy[index][j] != '1') //first non-space char has to be a 1 
		return (0);
	return (1);
}
char	get_map_char(t_map *map, int x, int y)
{
	int	len;
	
	if (y < 0 || y >= map->count || x < 0)
		return ('\0');
	if (!map->copy[y])
		return ('\0');
	
	len = ft_strlen(map->copy[y]);
	if (len > 0 && map->copy[y][len - 1] == '\n')
		len--;
	
	if (x >= len)
		return ('\0');
	
	return (map->copy[y][x]);
}
