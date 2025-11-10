/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_movement_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:40:43 by javi              #+#    #+#             */
/*   Updated: 2025/11/10 21:13:29 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	validate_move(t_cub3D *cub3D, float new_x, float new_y)
{
	int	moved;

	moved = 0;
	if (!is_wall(cub3D->map, (int)new_x, (int)cub3D->player->pos_y))
	{
		cub3D->player->pos_x = new_x;
		moved = 1;
	}
	if (!is_wall(cub3D->map, (int)cub3D->player->pos_x, (int)new_y))
	{
		cub3D->player->pos_y = new_y;
		moved = 1;
	}
	return (moved);
}

static int	move_direction(t_cub3D *cub3D, float dir_x, float dir_y, float speed)
{
	return (validate_move(cub3D, 
		cub3D->player->pos_x + dir_x * speed,
		cub3D->player->pos_y + dir_y * speed));
}
/*
	if we want to keep this function like this, then I think p->move_y etc,
	should be restored to 0 if the move is not "valid"
*/
int	move_player(t_cub3D *cub3D) 
{
	int			moved;
	t_player	*p;

	moved = 0;
	p = cub3D->player;
	if (p->move_y == 1)
		moved += move_direction(cub3D, p->dir_x, p->dir_y, MOVESPEED);
	else if (p->move_y == -1)
		moved += move_direction(cub3D, -p->dir_x, -p->dir_y, MOVESPEED);
	if (p->move_x == -1)
		moved += move_direction(cub3D, p->dir_y, -p->dir_x, MOVESPEED);
	else if (p->move_x == 1)
		moved += move_direction(cub3D, -p->dir_y, p->dir_x, MOVESPEED);
	if (p->rotate != 0)
		moved += rotate_player(cub3D, p->rotate);
	return (moved);
}

int	rotate_player(t_cub3D *cub3D, float rotdir)
{
	t_player	*p;
	float		tmp_x;
	float		rotspeed;

	p = cub3D->player;
	rotspeed = ROTSPEED * rotdir;
	tmp_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rotspeed) - p->dir_y * sin(rotspeed);
	p->dir_y = tmp_x * sin(rotspeed) + p->dir_y * cos(rotspeed);
	tmp_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rotspeed) - p->plane_y * sin(rotspeed);
	p->plane_y = tmp_x * sin(rotspeed) + p->plane_y * cos(rotspeed);
	return (1);
}

/**
 * game_loop - Main game loop called by mlx_loop_hook
 * This function is called continuously by MLX
 * It checks for player input and re-renders if needed
 */
// int	game_loop(void *param) //Alex: this function is unused so far, and I think unnecessary. (I can explain why if needed)
// {
// 	t_cub3D	*cub3D;
// 	int		moved;

// 	cub3D = (t_cub3D *)param;
// 	// Check if player has any movement inputs
// 	if (cub3D->player->move_x != 0 || cub3D->player->move_y != 0 
// 		|| cub3D->player->rotate != 0)
// 	{
// 		// Process movement
// 		moved = move_player(cub3D);
// 		// Only re-render if player actually moved
// 		if (moved)
// 		{
// 			render_3d_view(cub3D);
// 		}
// 	}
// 	return (0);
//} 
