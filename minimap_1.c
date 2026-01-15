/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javi <javi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 09:42:46 by javi              #+#    #+#             */
/*   Updated: 2025/11/10 17:32:00 by javi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * set_minimap_tile_pixels - Fill a square tile on the minimap
 */
void	set_minimap_tile_pixels(t_minimap *m, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < m->tile_size)
	{
		j = 0;
		while (j < m->tile_size)
		{
			my_mlx_pixel_put(&m->img, x + j, i + y, color);
			j++;
		}
		i++;
	}
}

/**
 * draw_minimap_tile - Draw one tile with appropriate color
 */
void	draw_minimap_tile(t_minimap *minimap, int x, int y)
{
	int	pixel_x;
	int	pixel_y;
	
	pixel_x = x * minimap->tile_size;
	pixel_y = y * minimap->tile_size;
	
	if (minimap->map[y][x] == 'P')
		set_minimap_tile_pixels(minimap, pixel_x, pixel_y, MMAP_COLOR_PLAYER);
	else if (minimap->map[y][x] == '1')
		set_minimap_tile_pixels(minimap, pixel_x, pixel_y, MMAP_COLOR_WALL);
	else if (minimap->map[y][x] == '0')
		set_minimap_tile_pixels(minimap, pixel_x, pixel_y, MMAP_COLOR_FLOOR);
	else if (minimap->map[y][x] == ' ')
		set_minimap_tile_pixels(minimap, pixel_x, pixel_y, MMAP_COLOR_SPACE);
}
/**
 * set_minimap_border - Draw border around minimap
 */
void	set_minimap_border(t_minimap *minimap, int color)
{
	int	size;
	int	x;
	int	y;

	size = MMAP_PIXEL_SIZE + minimap->tile_size;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x <= size)
		{
			if (x < 5 || x > size - 5 || y < 5 || y > size - 5)
				my_mlx_pixel_put(&minimap->img, x, y, color);
			x++;
		}
		y++;
	}
}
// Draw a thick pixel (3x3 square) for better visibility
static void	draw_thick_pixel(t_minimap *m, int x, int y, int color)
{
	int	dx;
	int	dy;

	dx = -1;
	while (dx <= 1)
	{
		dy = -1;
		while (dy <= 1)
		{
			my_mlx_pixel_put(&m->img, x + dx, y + dy, color);
			dy++;
		}
		dx++;
	}
}

/*
 * draw_minimap_ray - draw a thick line from the player's center in direction
 * of player->dir_x / dir_y. The line sticks to the character and is more visible.
 */
void draw_minimap_ray(t_minimap *m, t_player *p)
{
	int		center_x;
	int		center_y;
	int		i;
	int		max;
	float	lenf;
	float	step_x;
	float	step_y;

	center_x = (m->view_dist) * m->tile_size + (m->tile_size / 2);
	center_y = (m->view_dist) * m->tile_size + (m->tile_size / 2);
	lenf = (float)m->tile_size * 3.5f;
	max = (int)lenf;
	step_x = p->dir_x * (float)m->tile_size;
	step_y = p->dir_y * (float)m->tile_size;
	i = 0;
	while (i <= max)
	{
		int	rx;
		int	ry;

		rx = center_x + (int)(step_x * i / (float)m->tile_size);
		ry = center_y + (int)(step_y * i / (float)m->tile_size);
		draw_thick_pixel(m, rx, ry, 0xFF0000);
		i++;
	}
}
