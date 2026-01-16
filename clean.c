/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 23:41:31 by elavrich          #+#    #+#             */
/*   Updated: 2026/01/17 00:05:00 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void clean_all(t_cub3D *Cub3D)
{
    if(Cub3D->map->copy)
    {
       int i = 0;
        while (Cub3D->map->copy[i])
        {
            free(Cub3D->map->copy[i]);
            i++;
        }
        free(Cub3D->map->copy);
    }
    mlx_destroy_image(Cub3D->mlx, Cub3D->img.img);
    mlx_destroy_image(Cub3D->mlx, Cub3D->map->N_text.img);
    mlx_destroy_image(Cub3D->mlx, Cub3D->map->S_text.img);
    mlx_destroy_image(Cub3D->mlx, Cub3D->map->E_text.img);
    mlx_destroy_image(Cub3D->mlx, Cub3D->map->W_text.img);
    mlx_destroy_window(Cub3D->mlx, Cub3D->win);
    free(Cub3D->mlx);
}
