/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 01:48:46 by elavrich          #+#    #+#             */
/*   Updated: 2026/01/24 00:50:28 by elavrich         ###   ########.fr       */
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

//calculate_wall_height - Calculate screen height of wall slice
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

//normalize_angle - Keep angle within 0 to 2π range
float	normalize_angle(float angle)
{
	while (angle < 0)
		angle += 2 * PI;
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

//my_mlx_pixel_put - Fast pixel put to image buffer
void	my_mlx_pixel_put(t_cub_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
