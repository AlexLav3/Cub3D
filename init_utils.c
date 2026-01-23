/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 03:05:53 by elavrich          #+#    #+#             */
/*   Updated: 2026/01/24 00:42:32 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	player_found(t_cub3 *cub3, int actual_y, int x, int y)
{
	return ((cub3->map->copy[actual_y][x] == 'N'
		|| cub3->map->copy[actual_y][x] == 'S'
		|| cub3->map->copy[actual_y][x] == 'E'
		|| cub3->map->copy[actual_y][x] == 'W'));
}

void	player_var(t_cub3 *cub3, int y, int x, int a_y)
{
	cub3->player->dir = cub3->map->copy[a_y][x];
	cub3->player->pos_x = (float)x + 0.5;
	cub3->player->pos_y = (float)y + 0.5;
	cub3->map->copy[a_y][x] = '0';
}

void	set_text_add(t_cub_img *texture)
{
	if (texture->img)
	{
		texture->addr = mlx_get_data_addr(texture->img,
				&texture->bits_per_pixel, &texture->line_len, &texture->endian);
	}
}

int	set_textures_col(t_map *map, int op, char *path)
{
	int			width;
	int			height;
	int			len;
	t_cub_img	*texture;

	width = 64;
	height = 64;
	len = ft_strlen(path);
	while (len > 0 && (path[len - 1] == '\n' || path[len - 1] == ' ' || path[len- 1] == '\t'))
		path[--len] = '\0';
	if (op == NT)
		texture = &map->n_text;
	else if (op == ST)
		texture = &map->s_text;
	else if (op == ET)
		texture = &map->e_text;
	else if (op == WT)
		texture = &map->w_text;
	texture->img = mlx_xpm_file_to_image(map->cub3->mlx, path, &width, &height);
	if (!texture->img)
		return (printf("failed to load texture from '%s'\n", path), 0);
	return (set_text_add(texture), 1);
}
