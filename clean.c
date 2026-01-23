/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 23:41:31 by elavrich          #+#    #+#             */
/*   Updated: 2026/01/24 00:24:58 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	clean_imgs(t_cub3 *cub3)
{
	if (cub3->map->n_text.img)
		mlx_destroy_image(cub3->mlx, cub3->map->n_text.img);
	if (cub3->map->s_text.img)
		mlx_destroy_image(cub3->mlx, cub3->map->s_text.img);
	if (cub3->map->e_text.img)
		mlx_destroy_image(cub3->mlx, cub3->map->e_text.img);
	if (cub3->map->w_text.img)
		mlx_destroy_image(cub3->mlx, cub3->map->w_text.img);
	if (cub3->img.img)
		mlx_destroy_image(cub3->mlx, cub3->img.img);
	if (cub3->win)
		mlx_destroy_window(cub3->mlx, cub3->win);
}

void	map_errfree(char **map, int fd, int y)
{
	while (--y >= 0)
		free(map[y]);
	free(map);
	map = NULL;
	if (close(fd))
		perror("close");
	return ;
}
