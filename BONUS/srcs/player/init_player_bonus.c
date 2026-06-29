/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 13:54:59 by equintas          #+#    #+#             */
/*   Updated: 2026/06/10 14:54:33 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	init_player_on_north(t_game *game)
{
	game->player.dir_x = 0.0;
	game->player.dir_y = -1.0;
	game->player.plane_x = 0.66;
	game->player.plane_y = 0.0;
}

static void	init_player_on_south(t_game *game)
{
	game->player.dir_x = 0.0;
	game->player.dir_y = 1.0;
	game->player.plane_x = -0.66;
	game->player.plane_y = 0.0;
}

static void	init_player_on_west(t_game *game)
{
	game->player.dir_x = -1.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = -0.66;
}

static void	init_player_on_east(t_game *game)
{
	game->player.dir_x = 1.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.66;
}

void	init_player(t_game *game)
{
	char	dir;

	if (!game || !game->map)
		return ;
	game->player.pos_x = (double)game->pos_x + 0.5;
	game->player.pos_y = (double)game->pos_y + 0.5;
	dir = game->map[game->pos_y][game->pos_x];
	if (dir == 'N')
		init_player_on_north(game);
	else if (dir == 'S')
		init_player_on_south(game);
	else if (dir == 'W')
		init_player_on_west(game);
	else if (dir == 'E')
		init_player_on_east(game);
}
