/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:40:02 by javi              #+#    #+#             */
/*   Updated: 2025/11/11 04:12:25 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int create_rgb(int r, int g, int b)
{
	// printf("r %d\n", r);
	// printf("g %d\n", g);
	// printf("b %d\n", b);
	return (r << 16 | g << 8 | b);
}

/**
 * is_wall - Check if a map position contains a wall
 * @map: The game map structure
 * @x: X coordinate in map grid
 * @y: Y coordinate in map grid
 * 
 * Returns: 1 if wall ('1'), 0 if empty space ('0' or player spawn)
 */
int is_wall(t_map *map, int x, int y)
{
	// Bounds check - outside map is considered a wall
	if (y < 0 || y >= map->count || x < 0)
		return (1);
	
	if (!map->copy[y] || x >= (int)ft_strlen(map->copy[y]))
		return (1);
	
	// '1' is a wall, everything else is walkable - Alex: I had the "is walkable" variable for this (in case we will have doors, for example.)
	return (map->copy[y][x] == '1');
}

/**
 * normalize_angle - Keep angle within 0 to 2π range
 * @angle: The angle to normalize
 * 
 * Returns: Normalized angle
 */
float normalize_angle(float angle)
{
	while (angle < 0)
		angle += 2 * PI;
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}
/**
 * cast_single_ray - Cast one ray and find where it hits a wall
 * @player: Player position and angle
 * @map: Game map
 * @ray_angle: Direction to cast this ray
 * 
 * This is the heart of raycasting. We step forward in small increments
 * along the ray direction until we hit a wall.
 * 
 * Returns: Ray structure with hit information
 */
t_ray cast_single_ray(t_player *player, t_map *map, float ray_angle)
{
	t_ray   ray;
	float   ray_x;          // Current ray position X
	float   ray_y;          // Current ray position Y
	float   ray_dir_x;      // Ray direction X component
	float   ray_dir_y;      // Ray direction Y component
	float   distance;       // Total distance traveled
	int     map_x;          // Current map grid X
	int     map_y;          // Current map grid Y
	int   prev_map_x;
	// Initialize ray starting at player position
	ray_x = player->pos_x;
	ray_y = player->pos_y;
	
	// Calculate ray direction vector from angle
	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	
	// Start with zero distance
	distance = 0;
	// Store initial grid position
	prev_map_x = (int)ray_x;
	while (distance < MAX_DEPTH)
	{
		// Advance ray
		ray_x += ray_dir_x * RAY_STEP;
		ray_y += ray_dir_y * RAY_STEP;
		distance += RAY_STEP;
		
		// Get current grid cell
		map_x = (int)ray_x;
		map_y = (int)ray_y;
		
		// Check if we hit a wall
		if (is_wall(map, map_x, map_y))
		{
			// Store hit information
			ray.distance = distance;
			ray.angle = ray_angle;
			ray.wall_x = ray_x;
			ray.wall_y = ray_y;
			// Determine if we hit a vertical or horizontal wall
			// This is used to shade walls differently for depth perception
			if (prev_map_x != map_x)
				ray.hit_vertical = 1;  // Crossed vertical grid line (hit E/W wall)
			else
				ray.hit_vertical = 0;   // Crossed horizontal grid line (hit N/S wall)
			return (ray);
		}
		prev_map_x = map_x;
	}
	// No wall found within max depth - return max distance
	ray.distance = MAX_DEPTH;
	ray.angle = ray_angle;
	ray.wall_x = ray_x;
	ray.wall_y = ray_y;
	ray.hit_vertical = 0;
	return (ray);
}

/**
 * calculate_wall_height - Calculate screen height of wall slice
 * @distance: Distance from player to wall
 * 
 * Closer walls appear taller on screen. Alex: I feel something is missing bc the width is fucked.
 * We use inverse proportion: height = constant / distance
 * 
 * Returns: Height in pixels
 */
int calculate_wall_height(float distance)
{
	int height;
	
	// Avoid division by zero
	if (distance < 0.1)
		distance = 0.1;
	
	// Calculate wall height (perspective projection)
	// The constant (TILE_SIZE * SCREEN_HEIGHT) determines scaling
	height = (int)((TILE_SIZE * WIN_HEIGHT) / distance);
	
	// Clamp to reasonable values
	if (height > WIN_HEIGHT * 3)
		height = WIN_HEIGHT * 3;
	
	return (height);
}

/**
 * get_wall_color - Determine color for wall based on direction
 * @ray: The ray that hit the wall
 * 
 * We shade vertical and horizontal walls differently to create
 * depth perception (like lighting from above).
 * 
 * Returns: RGB color integer
 */
int get_wall_color(t_ray ray)
{
	t_color color;
	
	if (ray.hit_vertical)
	{
		// Vertical walls (North/South) - Lighter shade
		color.r = 200;
		color.g = 50;
		color.b = 50;
	}
	else
	{
		// Horizontal walls (East/West) - Darker shade
		color.r = 150;
		color.g = 30;
		color.b = 30;
	}
	
	// Optional: Add distance-based darkening (fog effect)
	float fog = 1.0 - (ray.distance / MAX_DEPTH);
	if (fog < 0.3)
		fog = 0.3;  // Don't go completely black
	
	color.r *= fog;
	color.g *= fog;
	color.b *= fog;
	
	return (create_rgb(color.r, color.g, color.b));
}

/**
 * draw_vertical_line - Draw one vertical stripe of the wall
 * @cub3D: Main game structure
 * @x: Screen X coordinate (column)
 * @wall_height: Height of wall to draw
 * @color: Color of the wall
 * 
 * This draws one vertical slice of wall, centered on screen.
 */
void draw_vertical_line(t_cub3D *cub3D, int x, int wall_height, int color)
{
	int y;
	int start_y;
	int end_y;
	
	// Calculate where wall starts and ends on screen (centered vertically)
	start_y = (WIN_HEIGHT / 2) - (wall_height / 2);
	end_y = start_y + wall_height;
	
	// Clamp to screen bounds
	if (start_y < 0)
		start_y = 0;
	if (end_y > WIN_HEIGHT)
		end_y = WIN_HEIGHT;
	
	// Draw ceiling (above wall) 
	y = 0;
	while (y < start_y)
	{
		mlx_pixel_put(cub3D->mlx, cub3D->win, x, y,
			create_rgb(cub3D->map->c_red, cub3D->map->c_green, cub3D->map->c_blue));
		y++;
	}
	
	// Draw wall
	y = start_y;
	while (y < end_y)
	{
		mlx_pixel_put(cub3D->mlx, cub3D->win, x, y, color);
		y++;
	}
	
	// Draw floor (below wall)
	y = end_y;
	while (y < WIN_HEIGHT)
	{
		mlx_pixel_put(cub3D->mlx, cub3D->win, x, y,
			create_rgb(cub3D->map->f_red, cub3D->map->f_green, cub3D->map->f_blue));
		y++;
	}
}
