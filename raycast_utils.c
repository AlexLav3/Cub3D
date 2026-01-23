/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 22:35:00 by jcouto            #+#    #+#             */
/*   Updated: 2026/01/24 00:49:30 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// calculate_wall_draw_bounds - Calculate start and end Y for wall drawing
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

// draw_wall_slice - Draw one vertical stripe of the wall
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
