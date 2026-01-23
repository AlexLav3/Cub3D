/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcouto <jcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 22:40:00 by jcouto            #+#    #+#             */
/*   Updated: 2026/01/23 00:07:38 by jcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * check_map_position_is_wall - Check if a map position contains a wall
 * @map: The game map structure
 * @x: X coordinate in map grid
 * @y: Y coordinate in map grid
 * 
 * Validates coordinates and checks if the position contains a wall ('1').
 * Returns 1 for walls or out-of-bounds, 0 for empty space.
 * 
 * Returns: 1 if wall or invalid position, 0 if empty space
 */
int	is_wall(t_map *map, int x, int y)
{
	int	actual_y;
	int	len;

	if (y < 0 || y >= (map->count - map->conf_end) || x < 0)
		return (1);
	actual_y = y + map->conf_end;
	if (!map->copy[actual_y])
		return (1);
	len = ft_strlen(map->copy[actual_y]);
	if (len > 0 && map->copy[actual_y][len - 1] == '\n')
		len--;
	if (x >= len)
		return (1);
	return (map->copy[actual_y][x] == '1');
}

/**
 * get_map_char - Get character at specific map coordinates
 * @map: Game map structure
 * @x: X coordinate in map grid
 * @y: Y coordinate in map grid
 * 
 * Returns: Character at position, or '\0' if out of bounds
 */
char	get_map_char(t_map *map, int x, int y)
{
	int	len;
	int	actual_y;

	if (y < 0 || y >= (map->count - map->conf_end) || x < 0)
		return ('\0');
	actual_y = y + map->conf_end;
	if (!map->copy[actual_y])
		return ('\0');
	len = ft_strlen(map->copy[actual_y]);
	if (len > 0 && map->copy[actual_y][len - 1] == '\n')
		len--;
	if (x >= len)
		return ('\0');
	return (map->copy[actual_y][x]);
}
