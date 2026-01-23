/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 22:40:00 by jcouto            #+#    #+#             */
/*   Updated: 2026/01/24 00:47:42 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
