/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_movement_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcouto <jcouto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:40:43 by javi              #+#    #+#             */
/*   Updated: 2026/01/23 00:10:42 by jcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	validate_move(t_cub3 *cub3, float new_x, float new_y)
{
	int	moved;

	moved = 0;
	if (!is_wall(cub3->map, (int)new_x, (int)cub3->player->pos_y))
	{
		cub3->player->pos_x = new_x;
		moved = 1;
	}
	if (!is_wall(cub3->map, (int)cub3->player->pos_x, (int)new_y))
	{
		cub3->player->pos_y = new_y;
		moved = 1;
	}
	return (moved);
}

static int	move_direction(t_cub3 *cub3, float dir_x, float dir_y,
		float speed)
{
	return (validate_move(cub3, cub3->player->pos_x + dir_x * speed,
			cub3->player->pos_y + dir_y * speed));
}

/*
	if we want to keep this function like this, then I think p->move_y etc,
	should be restored to 0 if the move is not "valid"
*/
int	move_player(t_cub3 *cub3)
{
	int			moved;
	t_player	*p;

	moved = 0;
	p = cub3->player;
	if (p->move_y == 1)
		moved += move_direction(cub3, p->dir_x, p->dir_y, MOVESPEED);
	else if (p->move_y == -1)
		moved += move_direction(cub3, -p->dir_x, -p->dir_y, MOVESPEED);
	if (p->move_x == -1)
		moved += move_direction(cub3, p->dir_y, -p->dir_x, MOVESPEED);
	else if (p->move_x == 1)
		moved += move_direction(cub3, -p->dir_y, p->dir_x, MOVESPEED);
	if (p->rotate != 0)
		moved += rotate_player(cub3, p->rotate);
	return (moved);
}

int	rotate_player(t_cub3 *cub3, float rotdir)
{
	t_player	*p;
	float		tmp_x;
	float		rotspeed;

	p = cub3->player;
	rotspeed = ROTSPEED * rotdir;
	tmp_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rotspeed) - p->dir_y * sin(rotspeed);
	p->dir_y = tmp_x * sin(rotspeed) + p->dir_y * cos(rotspeed);
	tmp_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rotspeed) - p->plane_y * sin(rotspeed);
	p->plane_y = tmp_x * sin(rotspeed) + p->plane_y * cos(rotspeed);
	return (1);
}
