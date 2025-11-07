/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:52:05 by elavrich          #+#    #+#             */
/*   Updated: 2025/11/07 17:27:31 by elavrich         ###   ########.fr       */
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
			i++;	
	}
}

char  *config_l(int fd)
{
	char *line;
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
	return line;
}
void sizem(t_cub3D *Cub3D) //size of map - if we decide to keep the window always full screen, this will need to be changed.
{
	int rows = Cub3D->map->conf_c;
	int columns = 0;
	while (Cub3D->map->copy[rows] != NULL)
		rows++;
	if (rows > 0)
		columns = ft_strlen(Cub3D->map->copy[0]) - 1;
	else
		columns = 0;
	Cub3D->w_height = rows * TILE_SIZE;
	Cub3D->w_width = columns * TILE_SIZE;
}

