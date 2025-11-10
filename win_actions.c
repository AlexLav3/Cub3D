/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javi <javi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:24:25 by elavrich          #+#    #+#             */
/*   Updated: 2025/11/10 17:33:41 by javi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_close(void *param)
{
	t_cub3D	*cub3D;

	cub3D = (t_cub3D *)param;
	
	// Destroy textures if they were loaded
	if (cub3D->map->N_text.img)
		mlx_destroy_image(cub3D->mlx, cub3D->map->N_text.img);
	if (cub3D->map->S_text.img)
		mlx_destroy_image(cub3D->mlx, cub3D->map->S_text.img);
	if (cub3D->map->E_text.img)
		mlx_destroy_image(cub3D->mlx, cub3D->map->E_text.img);
	if (cub3D->map->W_text.img)
		mlx_destroy_image(cub3D->mlx, cub3D->map->W_text.img);
	
	// Destroy main image buffer
	if (cub3D->img.img)
		mlx_destroy_image(cub3D->mlx, cub3D->img.img);
	
	// Destroy window
	if (cub3D->win)
		mlx_destroy_window(cub3D->mlx, cub3D->win);
	
	// Free map data
	if (cub3D->map && cub3D->map->copy)
	{
		int i = 0;
		while (cub3D->map->copy[i])
		{
			free(cub3D->map->copy[i]);
			i++;
		}
		free(cub3D->map->copy);
	}
	if (cub3D->map)
		free(cub3D->map);
	
	// Destroy display (this also frees mlx pointer)
	if (cub3D->mlx)
		mlx_destroy_display(cub3D->mlx);
	
	exit(0);
	return (0);
}

static void	handle_movement_keys(int keycode, t_player *p)
{
	if (keycode == W)
		p->move_y = 1;
	else if (keycode == S)
		p->move_y = -1;
	else if (keycode == A)
		p->move_x = -1;
	else if (keycode == D)
		p->move_x = 1;
}

static void	handle_rotation_keys(int keycode, t_player *p)
{
	if (keycode == XK_Left)
		p->rotate = -1;
	else if (keycode == XK_Right)
		p->rotate = 1;
}

int	ft_key_press(int keycode, void *v)
{
	t_cub3D	*cub3D;

	cub3D = v;
	if (keycode == XK_Escape)
		ft_close(cub3D);
	handle_movement_keys(keycode, cub3D->player);
	handle_rotation_keys(keycode, cub3D->player);
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
	t_cub3D	*cub3D;

	cub3D = v;
	release_movement_keys(keycode, cub3D->player);
	if ((keycode == XK_Left && cub3D->player->rotate == -1) ||
		(keycode == XK_Right && cub3D->player->rotate == 1))
		cub3D->player->rotate = 0;
	return (0);
}
