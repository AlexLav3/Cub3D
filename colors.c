/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:09:54 by jcouto            #+#    #+#             */
/*   Updated: 2026/01/24 00:46:55 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// create_rgb_color - Combine red, green, blue values into RGB integer
int create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

// calculate_fog_factor - Calculate fog/distance shading factor
static float calculate_fog_factor(float distance)
{
	float fog;

	fog = 1.0 - (distance / MAX_DEPTH);
	if (fog < 0.3)
		fog = 0.3;
	return (fog);
}

//get_wall_base_color - Get base color for wall based on hit direction
static t_color get_wall_base_color(int hit_vertical)
{
	t_color color;

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

// get_wall_color_with_fog - Determine color for wall with distance fog
int get_wall_color(t_ray ray)
{
	t_color color;
	float fog;

	color = get_wall_base_color(ray.hit_vertical);
	fog = calculate_fog_factor(ray.distance);
	color.r *= fog;
	color.g *= fog;
	color.b *= fog;
	return (create_rgb(color.r, color.g, color.b));
}
