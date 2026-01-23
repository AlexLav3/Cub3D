/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:24:35 by elavrich          #+#    #+#             */
/*   Updated: 2026/01/24 00:29:01 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_player_direction(t_cub3 *cub3)
{
	t_player	*p = cub3->player;
	int			i;

	i = 0;
	while (i < 4)
	{
		if (g_dirs[i].dir == p->dir)
		{
			p->dir_x = g_dirs[i].dir_x;
			p->dir_y = g_dirs[i].dir_y;
			p->plane_x = g_dirs[i].plane_x;
			p->plane_y = g_dirs[i].plane_y;
			return;
		}
		i++;
	}
}

static int	scan_map_row_for_player(t_cub3 *cub3, int y, int a_y, int *count)
{
	int	x;

	x = 0;
	while (cub3->map->copy[a_y][x] && cub3->map->copy[a_y][x] != '\n')
	{
		if (player_found(cub3, a_y, x, y))
		{
			if (*count > 0)
				return (printf("Error: Multiple player spawns found\n"), 0);
			player_var(cub3, y, x, a_y);
			(*count)++;
		}
		x++;
	}
	return (1);
}

int	init_player(t_cub3 *cub3)
{
	int	y;
	int	a_y;
	int	player_count;

	player_count = 0;
	y = 0;
	while (y < (cub3->map->count - cub3->map->conf_end))
	{
		a_y = y + cub3->map->conf_end;
		if (!cub3->map->copy[a_y])
			break ;
		if (!scan_map_row_for_player(cub3, y, a_y, &player_count))
			return (0);
		y++;
	}
	if (player_count == 0)
		return (printf("Error: No player spawn found\n"), 0);
	return (1);
}

int	mlx_set(t_cub3 *cub3)
{
	cub3->win = mlx_new_window(cub3->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3");
	if (!cub3->win)
		return (0);
	cub3->img.img = mlx_new_image(cub3->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cub3->img.img)
		return (0);
	cub3->img.addr = mlx_get_data_addr(cub3->img.img,
			&cub3->img.bits_per_pixel, &cub3->img.line_len,
			&cub3->img.endian);
	if (!configs(cub3->map))
		return (ft_close(cub3), 0);
	if (!walls_check(cub3->map))
		return (printf("Not enclosed by walls\n"), ft_close(cub3), 0);
	if (!init_player(cub3))
		return (ft_close(cub3), 0);
	init_player_direction(cub3);
	render_3d_view(cub3, 0);
	mlx_hook(cub3->win, 17, 0, ft_close, (void *)cub3);
	mlx_hook(cub3->win, 2, 1L << 0, ft_key_press, (void *)cub3);
	mlx_hook(cub3->win, 3, 1L << 1, ft_key_release, (void *)cub3);
	mlx_loop(cub3->mlx);
	return (1);
}

void	set_colors(t_map *map, int op, char *line)
{
	int	colors[3];

	extract_color(line, colors);
	if (op == F)
	{
		map->f_red = colors[0];
		map->f_green = colors[1];
		map->f_blue = colors[2];
	}
	else if (op == C)
	{
		map->c_red = colors[0];
		map->c_green = colors[1];
		map->c_blue = colors[2];
	}
}
