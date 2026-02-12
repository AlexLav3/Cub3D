/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcouto <jcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:10:59 by jcouto            #+#    #+#             */
/*   Updated: 2026/02/12 07:17:50 by jcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * init_ray_state - Initialize ray casting state from player position
 * @player: Player position and angle
 * @ray_angle: Direction to cast this ray
 * @state: Pointer to ray state structure to initialize
 * 
 * Sets up the starting position and direction for raycasting.
 */
static void	init_ray_state(t_player *player, float ray_angle,
	t_ray_state *state)
{
	state->x = player->pos_x;
	state->y = player->pos_y;
	state->dir_x = cos(ray_angle);
	state->dir_y = sin(ray_angle);
	state->distance = 0;
	state->prev_map_x = (int)floor(state->x);
	state->prev_map_y = (int)floor(state->y);
}

/**
 * step_ray_forward - Advance ray position by one step along its direction
 * @state: Pointer to ray state structure
 * 
 * Moves the ray forward by RAY_STEP distance and updates the total distance.
 */
static void	step_ray_forward(t_ray_state *state)
{
	state->x += state->dir_x * RAY_STEP;
	state->y += state->dir_y * RAY_STEP;
	state->distance += RAY_STEP;
}

/**
 * update_ray_on_hit - Update ray structure when wall is hit
 * @ray: Pointer to ray structure to update
 * @ray_angle: Direction of the ray
 * @state: Pointer to ray state structure
 * @map_x: Map X coordinate where wall was hit
 * 
 * Fills in the ray structure with hit information including distance,
 * position, and whether it hit a vertical or horizontal wall.
 */
static void	update_ray_on_hit(t_ray *ray, float ray_angle,
	t_ray_state *state, int map_x)
{
	ray->distance = state->distance;
	ray->angle = ray_angle;
	ray->wall_x = state->x;
	ray->wall_y = state->y;
	if (state->prev_map_x != map_x)
		ray->hit_vertical = 1;
	else
		ray->hit_vertical = 0;
}

/**
 * check_wall_collision - Check if ray hit a wall at current position
 * @map: Game map
 * @ray: Pointer to ray structure
 * @ray_angle: Direction of the ray
 * @state: Pointer to ray state structure
 * 
 * Returns: 1 if wall was hit, 0 otherwise
 */
static int	check_wall_collision(t_map *map, t_ray *ray, float ray_angle,
	t_ray_state *state)
{
	int	map_x;
	int	map_y;

	map_x = (int)floor(state->x);
	map_y = (int)floor(state->y);
if (is_wall(map, map_x, map_y))
	{
		update_ray_on_hit(ray, ray_angle, state, map_x);
		return (1);
	}
	if (state->prev_map_x != map_x && is_wall(map, state->prev_map_x, map_y))
	{
		update_ray_on_hit(ray, ray_angle, state, state->prev_map_x);
		return (1);
	}
	if (state->prev_map_y != map_y && is_wall(map, map_x, state->prev_map_y))
	{
		update_ray_on_hit(ray, ray_angle, state, map_x);
		return (1);
	}
	state->prev_map_x = map_x;
	state->prev_map_y = map_y;
	return (0);
}

/**
 * cast_single_ray - Cast one ray and find where it hits a wall
 * @player: Player position and angle
 * @map: Game map
 * @ray_angle: Direction to cast this ray
 * 
 * This is the core raycasting algorithm. We step forward in small increments
 * along the ray direction until we hit a wall or reach maximum depth.
 * 
 * Returns: Ray structure with hit information
 */
t_ray	cast_single_ray(t_player *player, t_map *map, float ray_angle)
{
	t_ray			ray;
	t_ray_state		state;

	init_ray_state(player, ray_angle, &state);
	while (state.distance < MAX_DEPTH)
	{
		step_ray_forward(&state);
		if (check_wall_collision(map, &ray, ray_angle, &state))
			return (ray);
	}
	ray.distance = MAX_DEPTH;
	ray.angle = ray_angle;
	ray.wall_x = state.x;
	ray.wall_y = state.y;
	ray.hit_vertical = 0;
	return (ray);
}
