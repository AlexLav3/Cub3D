/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:24:25 by elavrich          #+#    #+#             */
/*   Updated: 2026/01/23 23:41:16 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_close(void *param)
{
	t_cub3	*cub3;
	int		i;

	cub3 = (t_cub3 *)param;
	clean_imgs(cub3);
	if (cub3->map && cub3->map->copy)
	{
		i = 0;
		while (cub3->map->copy[i])
		{
			free(cub3->map->copy[i]);
			i++;
		}
		free(cub3->map->copy);
	}
	if (cub3->map)
		free(cub3->map);
	if (cub3->mlx)
		mlx_destroy_display(cub3->mlx);
	exit(0);
	return (0);
}

static int	handle_movement_keys(int keycode, t_player *p)
{
	if (keycode != W && keycode != S && keycode != A && keycode != D
		&& keycode != XK_Left && keycode != XK_Right)
		return (0);
	if (keycode == W)
		p->move_y = 1;
	else if (keycode == S)
		p->move_y = -1;
	else if (keycode == A)
		p->move_x = -1;
	else if (keycode == D)
		p->move_x = 1;
	else if (keycode == XK_Left)
		p->rotate = -1;
	else if (keycode == XK_Right)
		p->rotate = 1;
	return (1);
}

int	ft_key_press(int keycode, void *v)
{
	t_cub3	*cub3;

	cub3 = v;
	if (keycode == XK_Escape)
		ft_close(cub3);
	if (handle_movement_keys(keycode, cub3->player))
	{
		if (move_player(cub3))
			render_3d_view(cub3, 0);
	}
	return (0);
}

static void	release_movement_keys(int keycode, t_player *p)
{
	if ((keycode == W && p->move_y == 1) || (keycode == S && p->move_y == -1))
		p->move_y = 0;
	if ((keycode == A && p->move_x == -1) || (keycode == D && p->move_x == 1))
		p->move_x = 0;
}

int	ft_key_release(int keycode, void *v)
{
	t_cub3	*cub3;

	cub3 = v;
	release_movement_keys(keycode, cub3->player);
	if ((keycode == XK_Left && cub3->player->rotate == -1)
		|| (keycode == XK_Right && cub3->player->rotate == 1))
		cub3->player->rotate = 0;
	return (0);
}
