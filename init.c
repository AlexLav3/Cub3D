/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:24:35 by elavrich          #+#    #+#             */
/*   Updated: 2025/09/21 19:06:43 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int load_map(t_map *map)
{
    
}

int init_player(t_player *player)
{
    // player->pos_x = 2;
    // player->pos_y = 2;
}

int mlx_set(t_cub3D *Cub3D)
{
    Cub3D->win = mlx_new_window(Cub3D->mlx, 500, 600, "cub3D"); //temporary window sizes
    if(!Cub3D->win) //mlx new window has a malloc that can fail and return 0
        return 0;
    mlx_hook(Cub3D->win, 17, 0, ft_close, (void *)Cub3D);
    mlx_hook(Cub3D->win, 2, 1L << 0, ft_key_press, (void *)Cub3D);
    mlx_loop(Cub3D->mlx);
    return 1;
}
