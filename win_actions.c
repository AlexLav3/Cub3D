/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:24:25 by elavrich          #+#    #+#             */
/*   Updated: 2025/11/07 17:26:46 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//if this is not correct, ofc I can change it. 
void	p_actions(int keycode, t_player *player)
{
	if (keycode == W)
		move_player(player, cos(player->angle), sin(player->angle));
	else if (keycode == S)
		move_player(player, -cos(player->angle), -sin(player->angle));
	else if (keycode == D)
		move_player(player, sin(player->angle), -cos(player->angle));
	else if (keycode == A)
		move_player(player, -sin(player->angle), cos(player->angle));
	else if (keycode == XK_Right)
		player->angle += 0.05;
	else if (keycode == XK_Left)
		player->angle -= 0.05;
	if (player->angle < 0)
		player->angle += 2 * PI;
	if (player->angle >= 2 * PI)
		player->angle -= 2 * PI;
}

void	move_player(t_player *player, float x_factor, float y_factor)
{
	player->pos_x += x_factor * player->speed;
	player->pos_y += y_factor * player->speed;
}

int	ft_close(t_cub3D *cub3D)
{
	if (cub3D->win && cub3D->mlx)
		mlx_destroy_window(cub3D->mlx, cub3D->win);
	exit(0);
}
int	ft_key_press(int keycode, void *v)
{
	t_cub3D	*cub3D;

	cub3D = v;
	if (keycode == XK_Escape || keycode == 3)
	{
		ft_close(cub3D);
		return (0);
	}
	p_actions(keycode, cub3D->player);
	return (0);
}
