/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_operations_aux_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 14:58:21 by equintas          #+#    #+#             */
/*   Updated: 2026/06/27 15:02:59 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static int	get_map_width(char **map, int y)
{
	int	x;

	x = 0;
	while (map[y][x])
		x++;
	return (x);
}

void	init_door_frames(t_game *game)
{
	int	y;
	int	x;
	int	height;
	int	width;

	height = get_map_height(game);
	game->door_frame = malloc(sizeof(int *) * (height + 1));
	game->door_frame[height] = NULL;
	y = 0;
	while (y < height)
	{
		width = get_map_width(game->map, y);
		game->door_frame[y] = malloc(sizeof(int) * width);
		x = 0;
		while (x < width)
		{
			game->door_frame[y][x] = 0;
			x++;
		}
		y++;
	}
}
