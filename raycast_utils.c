/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcouto <jcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 22:35:00 by jcouto            #+#    #+#             */
/*   Updated: 2026/01/23 00:10:45 by jcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * calculate_wall_draw_bounds - Calculate start and end Y for wall drawing
 * @wall_height: Height of wall to draw in pixels
 * @start_y: Pointer to store start Y coordinate
 * @end_y: Pointer to store end Y coordinate
 * 
 * Centers the wall vertically and clamps to screen bounds.
 */
static void	calculate_wall_draw_bounds(int wall_height, int *start_y,
	int *end_y)
{
	*start_y = (WIN_HEIGHT / 2) - (wall_height / 2);
	*end_y = *start_y + wall_height;
	if (*start_y < 0)
		*start_y = 0;
	if (*end_y > WIN_HEIGHT)
		*end_y = WIN_HEIGHT;
}

/**
 * draw_wall_slice - Draw one vertical stripe of the wall
 * @cub3: Main game structure
 * @x: Screen X coordinate (column)
 * @wall_height: Height of wall to draw
 * @color: Color of the wall
 * 
 * Draws one vertical slice of wall, centered on screen, with ceiling
 * and floor filled around it.
 */
void	draw_vertical_line(t_cub3 *cub3, int x, int wall_height, int color)
{
	int	y;
	int	start_y;
	int	end_y;

	calculate_wall_draw_bounds(wall_height, &start_y, &end_y);
	put_walls_ceiling(cub3, 0, x, start_y);
	y = start_y;
	while (y < end_y)
	{
		mlx_pixel_put(cub3->mlx, cub3->win, x, y, color);
		y++;
	}
	put_walls_ceiling(cub3, end_y, x, WIN_HEIGHT);
}
