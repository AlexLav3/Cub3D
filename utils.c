/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:52:05 by elavrich          #+#    #+#             */
/*   Updated: 2025/09/22 19:56:13 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		extract_color(char *line, int *colors)
{
	int	i;
	int	count;
	int	val;

	i = 0;
	count = 0;
	val = 0;
	while (line[i] && count < 3)
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		val = 0;
		while (line[i] >= '0' && line[i] <= '9')
		{
			val = val * 10 + (line[i] - '0');
			i++;
		}
		colors[count++] = val;
		if (line[i] == ',')
		{
			i++;
		}
	}
}
