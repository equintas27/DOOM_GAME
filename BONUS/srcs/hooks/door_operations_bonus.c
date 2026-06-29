/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_operations_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 10:22:34 by equintas          #+#    #+#             */
/*   Updated: 2026/06/27 16:12:31 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	open_door_action(t_game *game)
{
	int	check_x;
	int	check_y;
	int	frame;

	check_x = (int)(game->player.pos_x + game->player.dir_x * 0.8);
	check_y = (int)(game->player.pos_y + game->player.dir_y * 0.8);
	if (game->map[check_y][check_x] != 'D'
		&& game->map[check_y][check_x] != 'O')
		return ;
	frame = game->door_frame[check_y][check_x];
	if (frame == 0)
		game->door_frame[check_y][check_x] = 1;
	else if (frame == 8)
		game->door_frame[check_y][check_x] = -1;
}

int	is_door_passable(t_game *game, int x, int y)
{
	if (game->map[y][x] != 'D' && game->map[y][x] != 'O')
		return (1);
	return (abs(game->door_frame[y][x]) >= 6);
}

void	free_door_frames(t_game *game)
{
	int	y;

	y = 0;
	while (game->door_frame[y])
	{
		free(game->door_frame[y]);
		y++;
	}
	free(game->door_frame);
}

void	update_door_animation(t_game *game)
{
	int			y;
	int			x;
	int			frame;

	game->door_anim_delay++;
	if (game->door_anim_delay < 4)
		return ;
	game->door_anim_delay = 0;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			frame = game->door_frame[y][x];
			if (frame > 0 && frame < 8)
				game->door_frame[y][x] = frame + 1;
			else if (frame < 0 && frame > -8)
				game->door_frame[y][x] = frame - 1;
			else if (frame == -8)
				game->door_frame[y][x] = 0;
			x++;
		}
		y++;
	}
}
