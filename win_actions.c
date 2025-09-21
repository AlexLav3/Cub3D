/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:24:25 by elavrich          #+#    #+#             */
/*   Updated: 2025/09/21 18:52:13 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	p_actions(int keycode, t_cub3D *cub3D)
{
   if (keycode == 115) // S
        cub3D->player->pos_y++;
    else if (keycode == 100) // D
        cub3D->player->pos_x++;
    else if (keycode == 119) // W
        cub3D->player->pos_y--;
    else if (keycode == 97) // A
        cub3D->player->pos_x--;
}

int	ft_close(t_cub3D *cub3D)
{
	if (cub3D->win && cub3D->mlx)
	{
		mlx_destroy_window(cub3D->mlx, cub3D->win);
	}
	exit(0);
}
int	ft_key_press(int keycode, void *v)
{
	t_cub3D	*cub3D;

	cub3D = v;
	if (keycode == XK_Escape || keycode == 3)
	{
		ft_close(cub3D);
		return 0;
	}
    p_actions(keycode, cub3D);
    return 0;
}
