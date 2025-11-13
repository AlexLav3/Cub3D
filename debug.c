/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:59:46 by javi              #+#    #+#             */
/*   Updated: 2025/11/13 20:29:38 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	debug_player_state(t_cub3D *cub3D, const char *context)
{
	if (!DEBUG_MODE)
		return;
	
	printf("\n=== PLAYER STATE: %s ===\n", context);
	printf("Position: (%.2f, %.2f)\n", 
		cub3D->player->pos_x, cub3D->player->pos_y);
	printf("Direction Vector: (%.2f, %.2f)\n", 
		cub3D->player->dir_x, cub3D->player->dir_y);
	printf("Camera Plane: (%.2f, %.2f)\n", 
		cub3D->player->plane_x, cub3D->player->plane_y);
	printf("Move Flags: move_x=%d, move_y=%d, rotate=%d\n",
		cub3D->player->move_x, cub3D->player->move_y, cub3D->player->rotate);
	printf("Has Moved: %d\n", cub3D->player->has_moved);
	printf("Facing: %c\n", cub3D->player->dir);
	printf("Angle (calculated): %.2f radians (%.1f degrees)\n",
		atan2(cub3D->player->dir_y, cub3D->player->dir_x),
		atan2(cub3D->player->dir_y, cub3D->player->dir_x) * 180 / PI);
	printf("========================\n\n");
}

void	debug_movement(t_cub3D *cub3D, const char *direction)
{
	if (!DEBUG_MOVEMENT)
		return;
	
	printf("[MOVEMENT] Attempting to move %s from (%.2f, %.2f)\n",
		direction, cub3D->player->pos_x, cub3D->player->pos_y);
}

void	debug_rotation(t_cub3D *cub3D, float rotdir)
{
	if (!DEBUG_ROTATION)
		return;
	
	printf("[ROTATION] Rotating %s by %.3f radians\n",
		rotdir > 0 ? "RIGHT" : "LEFT", ROTSPEED * rotdir);
	printf("  Before: dir=(%.2f, %.2f) plane=(%.2f, %.2f)\n",
		cub3D->player->dir_x, cub3D->player->dir_y,
		cub3D->player->plane_x, cub3D->player->plane_y);
}

void	debug_init_complete(t_cub3D *cub3D)
{
	if (!DEBUG_INIT)
		return;
	
	printf("\n╔════════════════════════════════════════╗\n");
	printf("║     INITIALIZATION COMPLETE            ║\n");
	printf("╚════════════════════════════════════════╝\n");
	printf("Map: %s\n", cub3D->map->file);
	printf("Map Dimensions: %d x %d\n", cub3D->map->width, cub3D->map->count);
	printf("Player Start: (%.2f, %.2f) facing %c\n",
		cub3D->player->pos_x, cub3D->player->pos_y, cub3D->player->dir);
	printf("Textures:\n");
	printf("  North: %s\n", cub3D->map->N_text.img ? "✓ Loaded" : "✗ Failed");
	printf("  South: %s\n", cub3D->map->S_text.img ? "✓ Loaded" : "✗ Failed");
	printf("  East:  %s\n", cub3D->map->E_text.img ? "✓ Loaded" : "✗ Failed");
	printf("  West:  %s\n", cub3D->map->W_text.img ? "✓ Loaded" : "✗ Failed");
	printf("Colors:\n");
	printf("  Floor: RGB(%d, %d, %d)\n",
		cub3D->map->f_red, cub3D->map->f_green, cub3D->map->f_blue);
	printf("  Ceiling: RGB(%d, %d, %d)\n",
		cub3D->map->c_red, cub3D->map->c_green, cub3D->map->c_blue);
	printf("════════════════════════════════════════\n\n");
}

void	debug_map_info(t_map *map)
{
	int	y;
	
	if (!DEBUG_INIT)
		return;
	
	printf("\n=== MAP CONTENT ===\n");
	y = 0;
	while (map->copy[y] && y < 20)  // Show first 20 lines max
	{
		printf("Line %2d: %s", y, map->copy[y]);
		if (!ft_strchr(map->copy[y], '\n'))
			printf("\n");
		y++;
	}
	if (map->copy[y])
		printf("... (%d more lines)\n", map->count - y);
	printf("===================\n\n");
}

static const char	*get_key_name(int keycode)
{
	if (keycode == W) return "W (Forward)";
	if (keycode == S) return "S (Backward)";
	if (keycode == A) return "A (Strafe Left)";
	if (keycode == D) return "D (Strafe Right)";
	if (keycode == XK_Left) return "Left Arrow (Rotate Left)";
	if (keycode == XK_Right) return "Right Arrow (Rotate Right)";
	if (keycode == XK_Escape) return "ESC (Quit)";
	return "Unknown Key";
}

void	debug_key_press(int keycode)
{
	if (!DEBUG_INPUT)
		return;
	
	printf("[INPUT] Key PRESSED: %s (code: %d)\n", get_key_name(keycode), keycode);
}

void	debug_key_release(int keycode)
{
	if (!DEBUG_INPUT)
		return;
	
	printf("[INPUT] Key RELEASED: %s (code: %d)\n", get_key_name(keycode), keycode);
}

void	debug_render_frame(int frame_count)
{
	static int last_print = 0;
	
	if (!DEBUG_RENDER)
		return;
	
	// Print every 60 frames (roughly once per second at 60fps)
	if (frame_count - last_print >= 60)
	{
		printf("[RENDER] Frame %d rendered\n", frame_count);
		last_print = frame_count;
	}
}

/**
 * debug_display_minimap - Display minimap in console for debugging
 */
void	debug_display_minimap(t_minimap *minimap)
{
	int	y;
	int	x;
	
	if (!DEBUG_MINIMAP)
		return;
	
	printf("\n=== MINIMAP DEBUG ===\n");
	printf("Size: %dx%d\n", minimap->size, minimap->size);
	printf("Tile size: %d pixels\n", minimap->tile_size);
	printf("Offset: (%d, %d)\n", minimap->offset_x, minimap->offset_y);
	printf("Map content:\n");
	
	y = 0;
	while (y < minimap->size && minimap->map[y])
	{
		x = 0;
		while (x < minimap->size)
		{
			if (minimap->map[y][x] == '\0')
				printf(" ");
			else
				printf("%c", minimap->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	printf("====================\n\n");
}

void	debug_print_map_raw(t_map *map)
{
	//int y = 0; like this , yes you are printing the whole cub file
	int y = map->conf_c; //this will print only the actual map lines without the configuration lines.
	
	printf("\n=== RAW MAP DEBUG ===\n");
	printf("Width: %d, Count: %d\n", map->width, map->count - map->conf_c); // - conf_c for the actual count of map lines.
	while (y < map->count && map->copy[y])
	{
		printf("Line %2d (len=%zu): [", y - map->conf_c, ft_strlen(map->copy[y]));
		for (int i = 0; map->copy[y][i]; i++)
		{
			if (map->copy[y][i] == '\n')
				printf("\\n");
			else if (map->copy[y][i] == ' ')
				printf("_");
			else
				printf("%c", map->copy[y][i]);
		}
		printf("]\n");
		y++;
	}
	printf("===================\n\n");
}

void	debug_player_spawn_simple(t_cub3D *cub3D)
{
	int player_x = (int)cub3D->player->pos_x;
	int player_y = (int)cub3D->player->pos_y;
	
	printf("\n🎮 PLAYER SPAWN:\n");
	printf("   Grid pos: [%d, %d]\n", player_x, player_y);
	printf("   Exact pos: (%.2f, %.2f)\n", cub3D->player->pos_x, cub3D->player->pos_y);
	printf("   File line: %d\n", player_y);
	printf("   Facing: %c (dir: %.2f, %.2f)\n", 
		cub3D->player->dir, cub3D->player->dir_x, cub3D->player->dir_y);
	printf("   Standing on: '%c'\n", get_map_char(cub3D->map, player_x, player_y));
	printf("\n");
}
