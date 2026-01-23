/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcouto <jcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:09:54 by jcouto            #+#    #+#             */
/*   Updated: 2026/01/23 00:09:56 by jcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * create_rgb_color - Combine red, green, blue values into RGB integer
 * @r: Red component (0-255)
 * @g: Green component (0-255)
 * @b: Blue component (0-255)
 * 
 * Returns: RGB color as integer (0xRRGGBB format)
 */
int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

/**
 * calculate_fog_factor - Calculate fog/distance shading factor
 * @distance: Distance from player to wall
 * 
 * Returns: Fog factor between 0.3 and 1.0 (closer = brighter)
 */
static float	calculate_fog_factor(float distance)
{
	float	fog;

	fog = 1.0 - (distance / MAX_DEPTH);
	if (fog < 0.3)
		fog = 0.3;
	return (fog);
}

/**
 * get_wall_base_color - Get base color for wall based on hit direction
 * @hit_vertical: 1 if hit vertical wall, 0 if horizontal
 * 
 * Vertical walls are slightly brighter to create depth perception.
 * 
 * Returns: Color structure with RGB values
 */
static t_color	get_wall_base_color(int hit_vertical)
{
	t_color	color;

	if (hit_vertical)
	{
		color.r = 200;
		color.g = 50;
		color.b = 50;
	}
	else
	{
		color.r = 150;
		color.g = 30;
		color.b = 30;
	}
	return (color);
}

/**
 * get_wall_color_with_fog - Determine color for wall with distance fog
 * @ray: The ray that hit the wall
 * 
 * We shade vertical and horizontal walls differently to create
 * depth perception, and apply fog based on distance.
 * 
 * Returns: RGB color integer
 */
int	get_wall_color(t_ray ray)
{
	t_color	color;
	float	fog;

	color = get_wall_base_color(ray.hit_vertical);
	fog = calculate_fog_factor(ray.distance);
	color.r *= fog;
	color.g *= fog;
	color.b *= fog;
	return (create_rgb(color.r, color.g, color.b));
}
