/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcouto <jcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:52:05 by elavrich          #+#    #+#             */
/*   Updated: 2026/01/23 00:11:20 by jcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	extract_color(char *line, int *colors)
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

	line = get_next_line(fd);
	while (line)
	{
		if (is_config_line(line) || line[0] == '\n')
			free(line);
		else
		{
			free(line);
			break ;
		}
		line = get_next_line(fd);
	}
	return (line);
}

int	iter_rows(t_map *map, int index, int iter, bool middle)
{
	int	j;

	if (!middle)
	{
		while (map->copy[index][iter] == ' ')
			iter++;
		while (map->copy[index][iter] != '\n' && map->copy[index][iter] != '\0')
		{
			if (map->copy[index][iter] != '1' && map->copy[index][iter] != ' ')
				return (0);
			iter++;
		}
		return (1);
	}
	while (map->copy[index][iter] == ' ')
		iter++;
	if (map->copy[index][iter] != '1')
		return (0);
	j = ft_strlen(map->copy[index]) - 1;
	while (map->copy[index][j] == ' ' || map->copy[index][j] == '\n')
		j--;
	if (map->copy[index][j] != '1')
		return (0);
	return (1);
}

void	set_texts_w(t_cub3 *cub3, int wall_height, t_ray ray)
{
	cub3->tmp->texture = get_wall_texture(cub3->map, ray);
	cub3->tmp->start_y = (WIN_HEIGHT / 2) - (wall_height / 2);
	cub3->tmp->end_y = cub3->tmp->start_y + wall_height;
	cub3->tmp->tex_x = calculate_texture_x(ray);
	cub3->tmp->tex_y_step = 64.0 / wall_height;
	cub3->tmp->tex_y_pos = 0;
}
