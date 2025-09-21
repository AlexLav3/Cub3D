/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:24:30 by elavrich          #+#    #+#             */
/*   Updated: 2025/09/21 19:07:06 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int argc, char **argv)
{
    if(arg_error(argc, argv))
        return 0;
    t_cub3D cub3D;
    t_player player;
    t_map   *tmap = malloc(sizeof(t_map));
    if(!tmap)
        return 1;
    cub3D.mlx = mlx_init(&cub3D);
    load_map(tmap);
    cub3D.player = &player;
    cub3D.map = tmap;
    if(!mlx_set(&cub3D))
        return 1;
    return 0;
}