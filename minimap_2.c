/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javi <javi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 08:50:28 by javi              #+#    #+#             */
/*   Updated: 2025/11/12 18:36:13 by javi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * get_minimap_offset - Calculate offset to center minimap on player
 * If player is near edge, shift minimap so edges don't go off screen
 */
int	get_minimap_offset(t_minimap *minimap, int mapsize, int pos)
{
	if (pos > minimap->view_dist && mapsize - pos > minimap->view_dist + 1)
		return (pos - minimap->view_dist);
	if (pos > minimap->view_dist && mapsize - pos <= minimap->view_dist + 1)
		return (mapsize - minimap->size);
	return (0);
}

/**
 * is_valid_map_coord - Check if coordinate is within map bounds
 */
int	is_valid_map_coord(int coord, int size)
{
	if (coord < size)
		return (1);
	return (0);
}

/**
 * add_minimap_line - Create one line of the minimap
 * P = player, 1 = wall, 0 = floor, \0 = void/out of bounds
 */
char	*add_minimap_line(t_cub3D *cub3D, t_minimap *m, int y)
{
	char	*line;
	int		x;
	int		player_x;
	int		player_y;
	char	map_char;

	line = malloc(sizeof(char) * (m->size + 1));
	if (!line)
		return (NULL);	
	
	player_x = (int)cub3D->player->pos_x;
	player_y = (int)cub3D->player->pos_y;
	
	x = 0;
	while (x < m->size)
	{
		if (player_x == (x + m->offset_x) && player_y == (y + m->offset_y))
			line[x] = 'P';
		else
		{
			map_char = get_map_char(cub3D->map, x + m->offset_x, y + m->offset_y);
			if (map_char == '1')
				line[x] = '1';
			else if (map_char == '0')
				line[x] = '0';
			else
				line[x] = ' ';  // Use space instead of '\0' for out of bounds
		}
		x++;
	}
	line[m->size] = '\0';
	return (line);
}
/*
 * generate_minimap - Create full minimap char array centered on player
 */
 
char	**generate_minimap(t_cub3D *cub3D, t_minimap *minimap)
{
	char	**mmap;
	int		y;

	mmap = malloc(sizeof(char *) * (minimap->size + 1));
	if (!mmap)
		return (NULL);	
	y = 0;
	while (y < minimap->size)
	{
		mmap[y] = add_minimap_line(cub3D, minimap, y);
		if (!mmap[y])
		{
			while (--y >= 0)
				free(mmap[y]);
			free(mmap);
			return (NULL);
		}
		y++;
	}
	mmap[minimap->size] = NULL;
	return (mmap);
}
