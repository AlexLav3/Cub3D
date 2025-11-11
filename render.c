/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 07:29:25 by javi              #+#    #+#             */
/*   Updated: 2025/11/11 23:57:12 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * my_mlx_pixel_put - Fast pixel put to image buffer
 * Instead of mlx_pixel_put which updates screen immediately (slow),
 * we write directly to image memory (fast), then display once
 */
void my_mlx_pixel_put(t_cub_img *img, int x, int y, int color)
{
	char *dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return;
	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
/**
 * get_texture_color - Sample a color from a texture at given coordinates
 * @texture: The texture image to sample from
 * @tex_x: X coordinate in texture (0-63)
 * @tex_y: Y coordinate in texture (0-63)
 * Returns: RGB color from texture
 */
int get_texture_color(t_cub_img *texture, int tex_x, int tex_y)
{
	char *pixel;
	
	if (!texture || !texture->addr)
		return (printf("Warning: trying to use missing texture\n"), 0xFF00FF); // Return magenta if texture missing
	// Clamp coordinates to texture bounds
	if (tex_x < 0) tex_x = 0;
	if (tex_x >= 64) tex_x = 63;
	if (tex_y < 0) tex_y = 0;
	if (tex_y >= 64) tex_y = 63;
	
	pixel = texture->addr + (tex_y * texture->line_len + tex_x * (texture->bits_per_pixel / 8));
	return (*(unsigned int*)pixel);
}

/**
 * get_wall_texture - Determine which texture to use based on wall hit
 * @map: Game map with loaded textures
 * @ray: Ray that hit the wall
 * @player_angle: Player's viewing angle
 * 
 * Returns: Pointer to the appropriate texture
 */
t_cub_img *get_wall_texture(t_map *map, t_ray ray)
{
	if (ray.hit_vertical)
	{
		// Vertical wall (East or West face)
		if (cos(ray.angle) > 0)
			return (&map->E_text); // Ray moving right → hit East wall
		else
			return (&map->W_text); // Ray moving left → hit West wall
	}
	else
	{
		// Horizontal wall (North or South face)
		if (sin(ray.angle) > 0)
			return (&map->S_text); // Ray moving down → hit South wall
		else
			return (&map->N_text); // Ray moving up → hit North wall
	}
}

/**
 * calculate_texture_x - Calculate X coordinate in texture
 * @ray: Ray that hit the wall
 * 
 * Returns: X coordinate in texture (0-63)
 */
int calculate_texture_x(t_ray ray)
{
	float wall_hit_pos;
	int tex_x;
	// Choose coordinate based on wall orientation
	if (ray.hit_vertical)
		wall_hit_pos = ray.wall_y;  // Vertical wall: use Y
	else
		wall_hit_pos = ray.wall_x;  // Horizontal wall: use X
	// Get fractional part (0.0 to 1.0)
	wall_hit_pos = wall_hit_pos - floor(wall_hit_pos);
	// Convert to texture coordinate (0 to 63)
	tex_x = (int)(wall_hit_pos * 64.0);
	// Ensure we're in bounds
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= 64)
		tex_x = 63;
	
	return (tex_x);
}
/**
 * draw_textured_wall - Draw one vertical stripe with texture
 */
void draw_textured_wall(t_cub3D *cub3D, int x, int wall_height, t_ray ray)
{
	int		y;
	int		start_y;
	int		end_y;
	int		tex_x;
	int		tex_y;
	float	tex_y_step;
	float	tex_y_pos;
	t_cub_img	*texture;
	int		color;
	
	// Get which texture to use
	texture = get_wall_texture(cub3D->map, ray);	
	// Calculate wall boundaries
	start_y = (WIN_HEIGHT / 2) - (wall_height / 2);
	//printf("start_y: %d\n", start_y); //-600 from the start, something seems off.
	end_y = start_y + wall_height;
	// Calculate texture X coordinate
	tex_x = calculate_texture_x(ray);	
	// Calculate how much to increment texture Y per screen pixel
	tex_y_step = 64.0 / wall_height;
	tex_y_pos = 0;
	// Adjust for off-screen parts
	if (start_y < 0)
	{
		tex_y_pos = -start_y * tex_y_step;
		start_y = 0;
	}
	if (end_y > WIN_HEIGHT)
		end_y = WIN_HEIGHT;
	// Draw ceiling
	y = 0;
	//start_y = 100; //just for testing, as the while loop never happens at all otherwise (I wanted to see if any color was displayed, spoiler, yep.)
	while (y < start_y)
	{
		//printf("this never happens");
		my_mlx_pixel_put(&cub3D->img, x, y,
			create_rgb(cub3D->map->c_red, cub3D->map->c_green, cub3D->map->c_blue));
		y++;
	}
	// Draw textured wall
	y = start_y;
	while (y < end_y)
	{
		tex_y = (int)tex_y_pos;
		color = get_texture_color(texture, tex_x, tex_y);
		my_mlx_pixel_put(&cub3D->img, x, y, color);
		tex_y_pos += tex_y_step;
		y++;
	}
	// Draw floor
	y = end_y;
	//y = 100; //again only for testing - renders at the top as ceiling, not bottom as floor.
	while (y < WIN_HEIGHT)
	{
		//printf("hi\n");
		my_mlx_pixel_put(&cub3D->img, x, y,
			create_rgb(cub3D->map->f_red, cub3D->map->f_green, cub3D->map->f_blue));
		y++;
	}
}
/**
 * render_3d_view - Main rendering function that casts rays and draws the scene
 * @cub3D: Main game structure
 * 
 * This function:
 * 1. Casts one ray per screen column (800 rays for 800 pixel width)
 * 2. Calculates the angle for each ray relative to player's view
 * 3. Draws each wall slice based on distance - does it also change which slice of the texture?
 */
void render_3d_view(t_cub3D *cub3D) //why floats used and not double? float can have issues rounding up/down
{
	int		x;
	float	camera_x;       // X-coordinate in camera space (-1 to +1)
	float	ray_dir_x;      // Ray direction X
	float	ray_dir_y;      // Ray direction Y
	float	ray_angle;      // Calculated angle for this ray
	t_ray	ray;
	int		wall_height;
	float	perpendicular_distance;
	t_player *p;

	p = cub3D->player;
	x = 0;
	while (x < WIN_WIDTH)
	{
		// Calculate camera X (-1 = left side, +1 = right side of screen)
		camera_x = 2 * x / (float)WIN_WIDTH - 1;
		// Calculate ray direction using player direction and camera plane
		ray_dir_x = p->dir_x + p->plane_x * camera_x;
		ray_dir_y = p->dir_y + p->plane_y * camera_x;
		// Calculate angle from direction vector (for texture selection)
		ray_angle = atan2(ray_dir_y, ray_dir_x);
		ray = cast_single_ray(cub3D->player, cub3D->map, ray_angle);
			
		// Calculate angle difference from camera center
		float player_angle = atan2(p->dir_y, p->dir_x);
		float angle_diff = ray_angle - player_angle;
			
		// Normalize angle difference to [-π, π]
		while (angle_diff > PI)
			 angle_diff -= 2 * PI;
		while (angle_diff < -PI) 
			angle_diff += 2 * PI;

		// Apply fisheye correction
		perpendicular_distance = ray.distance * cos(angle_diff);
		wall_height = calculate_wall_height(perpendicular_distance);
		// Draw with texture
		draw_textured_wall(cub3D, x, wall_height, ray);
		x++;
	}
	mlx_put_image_to_window(cub3D->mlx, cub3D->win, cub3D->img.img, 0, 0); 
	render_minimap(cub3D);
}
