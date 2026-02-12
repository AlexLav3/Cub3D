/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcouto <jcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 01:48:46 by elavrich          #+#    #+#             */
/*   Updated: 2026/02/12 07:26:36 by jcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_walls_ceiling(t_cub3 *cub3, int y, int x, int draw_end)
{
	if (y == 0)
	{
		while (y < draw_end)
		{
			my_mlx_pixel_put(&cub3->img, x, y, create_rgb(cub3->map->c_red,
					cub3->map->c_green, cub3->map->c_blue));
			y++;
		}
	}
	else
	{
		while (y < draw_end)
		{
			my_mlx_pixel_put(&cub3->img, x, y, create_rgb(cub3->map->f_red,
					cub3->map->f_green, cub3->map->f_blue));
			y++;
		}
	}
}

/**
 * calculate_wall_height - Calculate screen height of wall slice
 * @distance: Distance from player to wall
 * 

	* Closer walls appear taller on screen.
 * We use inverse proportion: height = constant / distance
 * 
 * Returns: Height in pixels
 */
int	calculate_wall_height(float distance)
{
	int	height;

	if (distance < 0.01)
		distance = 0.01;
	height = (int)(WIN_HEIGHT / distance);
	if (height > WIN_HEIGHT * 3)
		height = WIN_HEIGHT * 3;
	return (height);
}

/**
 * normalize_angle - Keep angle within 0 to 2π range
 * @angle: The angle to normalize
 * 
 * Returns: Normalized angle
 */
float	normalize_angle(float angle)
{
	while (angle < 0)
		angle += 2 * PI;
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

/**
 * my_mlx_pixel_put - Fast pixel put to image buffer
 * Instead of mlx_pixel_put which updates screen immediately (slow),
 * we write directly to image memory (fast), then display once
 */
void	my_mlx_pixel_put(t_cub_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
