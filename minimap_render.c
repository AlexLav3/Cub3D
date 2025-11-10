/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javi <javi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:25:18 by javi              #+#    #+#             */
/*   Updated: 2025/11/10 17:42:29 by javi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
 * render_minimap_image - create image, call draw loop, draw ray, put to window.
 * Uses minimap->img as the local image object (same pattern you already used).
 */
void render_minimap_image(t_cub3D *cub3D, t_minimap *minimap)
{
	int img_size;
	int screen_x;
	int screen_y;
	int x;
	int y;

	img_size = MMAP_PIXEL_SIZE + minimap->tile_size;

	/* create mlx image and get buffer info */
	minimap->img.img = mlx_new_image(cub3D->mlx, img_size, img_size);
	if (!minimap->img.img)
		return;

	minimap->img.addr = mlx_get_data_addr(minimap->img.img,
			&minimap->img.bits_per_pixel, &minimap->img.line_len,
			&minimap->img.endian);

	/* draw tiles */
	y = 0;
	while (y < minimap->size)
	{
		x = 0;
		while (x < minimap->size && minimap->map[y] && minimap->map[y][x])
		{
			draw_minimap_tile(minimap, x, y);
			x++;
		}
		y++;
	}
	/* draw ray (player pointer is in cub3D->player) */
	draw_minimap_ray(minimap, cub3D->player);
	/* border */
	set_minimap_border(minimap, MMAP_COLOR_SPACE);
	/* put in bottom-left corner */
	screen_x = minimap->tile_size;
	screen_y = WIN_HEIGHT - (MMAP_PIXEL_SIZE + (minimap->tile_size * 2));
	mlx_put_image_to_window(cub3D->mlx, cub3D->win, minimap->img.img,
		screen_x, screen_y);
	mlx_destroy_image(cub3D->mlx, minimap->img.img);
}

/*
 * render_minimap - top level: prepare minimap metadata, generate char map,
 * call render_minimap_image, then free.
 */
void render_minimap(t_cub3D *cub3D)
{
	t_minimap minimap;
	int i;

	minimap.map = NULL;
	minimap.view_dist = MMAP_VIEW_DIST;
	minimap.size = (2 * minimap.view_dist) + 1;
	minimap.tile_size = MMAP_PIXEL_SIZE / (2 * minimap.view_dist);

	minimap.offset_x = get_minimap_offset(&minimap,
			cub3D->map->width, (int)cub3D->player->pos_x);
	minimap.offset_y = get_minimap_offset(&minimap,
			cub3D->map->count, (int)cub3D->player->pos_y);

	minimap.map = generate_minimap(cub3D, &minimap);
	if (!minimap.map)
	{
		printf("Error: Failed to generate minimap\n");
		return;
	}

	if (DEBUG_MINIMAP)
		debug_display_minimap(&minimap);

	render_minimap_image(cub3D, &minimap);

	/* cleanup char map */
	i = 0;
	while (minimap.map[i])
	{
		free(minimap.map[i]);
		i++;
	}
	free(minimap.map);
}
