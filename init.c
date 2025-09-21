/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:24:35 by elavrich          #+#    #+#             */
/*   Updated: 2025/09/21 22:44:04 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	load_map(t_map *map)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open(map->file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	map->count = count;
	map->copy = malloc((count + 1) * sizeof(char *));
	if (!map->copy)
		return 0;
    //populate copy
    return 1;
}

int	init_player(t_cub3D *cub3D)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (cub3D->map->copy[y])
	{
        x = 0;
		while (cub3D->map->copy[y][x])
		{
            if (cub3D->map->copy[y][x] == 'N')
			{
                cub3D->map->copy[y][x] = '0';
				cub3D->player->pos_x = x;
				cub3D->player->pos_y = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	mlx_set(t_cub3D *Cub3D)
{
	Cub3D->win = mlx_new_window(Cub3D->mlx, Cub3D->w_height, Cub3D->w_width, "cub3D"); //temporary window sizes
	if (!Cub3D->win)
		return (0);
	mlx_hook(Cub3D->win, 17, 0, ft_close, (void *)Cub3D);
	mlx_hook(Cub3D->win, 2, 1L << 0, ft_key_press, (void *)Cub3D);
	mlx_loop(Cub3D->mlx);
	return (1);
}

void	set_textures(t_cub3D *cub3D)
{

	cub3D->map->floor = mlx_xpm_file_to_image(cub3D->mlx, "textures/floor.xpm", TILE_SIZE,
			TILE_SIZE);
	cub3D->map->wall = mlx_xpm_file_to_image(cub3D->mlx, "textures/wall.xpm", TILE_SIZE,
			TILE_SIZE);
}