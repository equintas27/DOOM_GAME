/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 14:18:42 by lkingui           #+#    #+#             */
/*   Updated: 2026/06/29 10:45:30 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	check_dir(t_game *game, int dx)
{
	if (dx < 0)
		game->player.dir_x = 1;
	else if (dx > 0)
		game->player.dir_x = 0;
}

void	move_player(t_game *game, double dx, double dy)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + dx;
	new_y = game->player.pos_y + dy;
	game->map[(int)game->player.pos_y][(int)game->player.pos_x] = '0';
	game->map[(int)game->player.pos_y][(int)game->player.pos_x] = '0';
	game->map[(int)new_y][(int)new_x] = 'N';
	game->player.pos_x = new_x;
	game->player.pos_y = new_y;
	render_frame(game);
}

int	call_move_player(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
	{
		cleanup_game(game);
		exit(0);
		return (0);
	}
	else if (keycode == XK_w)
		move_player(game, game->player.dir_x, game->player.dir_y);
	else if (keycode == XK_s)
		move_player(game, game->player.dir_x, game->player.dir_y);
	return (0);
}

int	mouse_hook(int x, int y, t_game *game)
{
	double	delta_x;
	int		center_x;

	(void)y;
	center_x = WIDTH / 2;
	delta_x = x - center_x;
	if (delta_x > 0)
		rotate(game, delta_x * 0.001);
	else if (delta_x < 0)
		rotate(game, delta_x * 0.001);
	mlx_mouse_move(game->mlx, game->win, center_x, HEIGHT / 2);
	return (0);
}

void	rotate(t_game *game, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rot) - game->player.dir_y
		* sin(rot);
	game->player.dir_y = old_dir_x * sin(rot) + game->player.dir_y * cos(rot);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot)
		- game->player.plane_y * sin(rot);
	game->player.plane_y = old_plane_x * sin(rot) + game->player.plane_y
		* cos(rot);
}
