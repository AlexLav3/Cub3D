/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcouto <jcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 07:29:25 by javi              #+#    #+#             */
/*   Updated: 2026/02/12 07:59:45 by jcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * get_texture_color - Sample a color from a texture at given coordinates
 * @texture: The texture image to sample from
 * @tex_x: X coordinate in texture (0-63)
 * @tex_y: Y coordinate in texture (0-63)
 * Returns: RGB color from texture
 */
int	get_texture_color(t_cub_img *texture, int tex_x, int tex_y)
{
	char	*pixel;

	if (!texture || !texture->addr)
		return (printf("Warning: trying to use missing texture\n"), 0xFF00FF);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= 64)
		tex_x = 63;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= 64)
		tex_y = 63;
	pixel = texture->addr + (tex_y * texture->line_len + tex_x
			* (texture->bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

/**
 * get_wall_texture - Determine which texture to use based on wall hit
 * @map: Game map with loaded textures
 * @ray: Ray that hit the wall
 * @player_angle: Player's viewing angle
 * 
 * Returns: Pointer to the appropriate texture
 */
t_cub_img	*get_wall_texture(t_map *map, t_ray ray)
{
	if (ray.hit_vertical)
	{
		if (cos(ray.angle) > 0)
			return (&map->e_text);
		else
			return (&map->w_text);
	}
	else
	{
		if (sin(ray.angle) > 0)
			return (&map->s_text);
		else
			return (&map->n_text);
	}
}

/**
 * calculate_texture_x - Calculate X coordinate in texture
 * @ray: Ray that hit the wall
 * 
 * Returns: X coordinate in texture (0-63)
 */
int	calculate_texture_x(t_ray ray)
{
	float	wall_hit_pos;
	int		tex_x;

	if (ray.hit_vertical)
		wall_hit_pos = ray.wall_y;
	else
		wall_hit_pos = ray.wall_x;
	wall_hit_pos = wall_hit_pos - floor(wall_hit_pos);
	tex_x = (int)(wall_hit_pos * 64.0);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= 64)
		tex_x = 63;
	return (tex_x);
}

/**
 * draw_textured_wall - Draw one vertical stripe with texture
 * 
 * P.s. variables moved to a struct with a temporary name (t_tmp), Iidk how
 */
void	draw_textured_wall(t_cub3 *cub3, int x, int wall_height, t_ray ray)
{
	int					y;
	t_texture_params	tmp;

	cub3->tmp = &tmp;
	set_texts_w(cub3, wall_height, ray);
	if (cub3->tmp->start_y < 0)
	{
		cub3->tmp->tex_y_pos = -cub3->tmp->start_y * cub3->tmp->tex_y_step;
		cub3->tmp->start_y = 0;
	}
	if (cub3->tmp->end_y > WIN_HEIGHT)
		cub3->tmp->end_y = WIN_HEIGHT;
	put_walls_ceiling(cub3, 0, x, cub3->tmp->start_y);
	y = cub3->tmp->start_y;
	while (y <= cub3->tmp->end_y)
	{
		cub3->tmp->tex_y = (int)cub3->tmp->tex_y_pos;
		cub3->tmp->color = get_texture_color(cub3->tmp->texture,
				cub3->tmp->tex_x, cub3->tmp->tex_y);
		my_mlx_pixel_put(&cub3->img, x, y, cub3->tmp->color);
		cub3->tmp->tex_y_pos += cub3->tmp->tex_y_step;
		y++;
	}
	put_walls_ceiling(cub3, cub3->tmp->end_y, x, WIN_HEIGHT);
}

/**
 * render_3d_view - Main rendering function that casts rays and draws the scene
 * @cub3: Main game structure
 * 
 * This function:
 * 1. Casts one ray per screen column (800 rays for 800 pixel width)
 * 2. Calculates the angle for each ray relative to player's view
 * 3. Draws each wall slice based on distance
	- does it also change which slice of the texture?
 */
void	render_3d_view(t_cub3 *cub3, int x)
{
	t_ray		ray;
	t_player	*p;

	p = cub3->player;
	while (x < WIN_WIDTH)
	{
		cub3->camera_x = 2 * x / (float)WIN_WIDTH - 1;
		cub3->ray_dir_x = p->dir_x + p->plane_x * cub3->camera_x;
		cub3->ray_dir_y = p->dir_y + p->plane_y * cub3->camera_x;
		cub3->ray_angle = atan2(cub3->ray_dir_y, cub3->ray_dir_x);
		ray = cast_single_ray(cub3->player, cub3->map, cub3->ray_angle);
		cub3->player_angle = atan2(p->dir_y, p->dir_x);
		cub3->angle_diff = cub3->ray_angle - cub3->player_angle;
		while (cub3->angle_diff > PI)
			cub3->angle_diff -= 2 * PI;
		while (cub3->angle_diff < -PI)
			cub3->angle_diff += 2 * PI;
		cub3->perpendicular_distance = ray.distance * cos(cub3->angle_diff);
		cub3->wall_height = calculate_wall_height(cub3->perpendicular_distance);
		draw_textured_wall(cub3, x, cub3->wall_height, ray);
		x++;
	}
	mlx_put_image_to_window(cub3->mlx, cub3->win, cub3->img.img, 0, 0);
}
