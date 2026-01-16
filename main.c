/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:24:30 by elavrich          #+#    #+#             */
/*   Updated: 2026/01/16 23:56:13 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_cub3D		cub3D;
	t_player	player;
	t_map		*tmap;

	if (arg_error(argc, argv))
		return (0);
	tmap = malloc(sizeof(t_map));
	if (!tmap)
		return (1);
	cub3D.mlx = mlx_init(&cub3D);
	if(!cub3D.mlx)
		return 1;
	tmap->file = argv[1];
	if (!load_map(tmap))
		return (free(tmap), 1);
	ft_memset(&player, 0, sizeof(t_player));
	player.speed = MOVESPEED;
	cub3D.player = &player;
	cub3D.player->speed = 0.1;
	cub3D.map = tmap;
	tmap->cub3D = &cub3D;
	if (!mlx_set(&cub3D))
		return (free(tmap), 1);
	return (0);
}
