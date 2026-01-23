/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:10:59 by jcouto            #+#    #+#             */
/*   Updated: 2026/01/24 00:50:09 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//init_ray_state - Initialize ray casting state from player position
static void	init_ray_state(t_player *player, float ray_angle,
	t_ray_state *state)
{
	state->x = player->pos_x;
	state->y = player->pos_y;
	state->dir_x = cos(ray_angle);
	state->dir_y = sin(ray_angle);
	state->distance = 0;
	state->prev_map_x = (int)state->x;
}

//step_ray_forward - Advance ray position by one step along its direction
static void	step_ray_forward(t_ray_state *state)
{
	state->x += state->dir_x * RAY_STEP;
	state->y += state->dir_y * RAY_STEP;
	state->distance += RAY_STEP;
}

//update_ray_on_hit - Update ray structure when wall is hit
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

//check_wall_collision - Check if ray hit a wall at current position
static int	check_wall_collision(t_map *map, t_ray *ray, float ray_angle,
	t_ray_state *state)
{
	int	map_x;
	int	map_y;

	map_x = (int)state->x;
	map_y = (int)state->y;
	if (is_wall(map, map_x, map_y))
	{
		update_ray_on_hit(ray, ray_angle, state, map_x);
		return (1);
	}
	state->prev_map_x = map_x;
	return (0);
}

//cast_single_ray - Cast one ray and find where it hits a wall
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
