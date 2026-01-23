/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:24:30 by elavrich          #+#    #+#             */
/*   Updated: 2026/01/24 00:17:03 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_cub3		cub3;
	t_player	player;
	t_map		*tmap;

	if (arg_error(argc, argv))
		return (0);
	tmap = calloc(1, sizeof(t_map));
	if (!tmap)
		return (1);
	cub3.mlx = mlx_init(&cub3);
	if (!cub3.mlx)
		return (1);
	tmap->file = argv[1];
	if (!load_map(tmap))
		return (free(tmap), 1);
	ft_memset(&player, 0, sizeof(t_player));
	player.speed = MOVESPEED;
	cub3.player = &player;
	cub3.player->speed = 0.1;
	cub3.map = tmap;
	tmap->cub3 = &cub3;
	if (!mlx_set(&cub3))
		return (free(tmap), 1);
	return (0);
}
