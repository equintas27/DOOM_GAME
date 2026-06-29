/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 10:37:47 by equintas          #+#    #+#             */
/*   Updated: 2026/06/27 14:00:25 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

#define MOVE_SPEED 0.002

int	close_window(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}

int	key_press(int key_press, t_game *game)
{
	if (key_press == XK_Escape)
	{
		cleanup_game(game);
		exit(0);
		return (0);
	}
	if (key_press == XK_e)
		open_door_action(game);
	if (key_press == XK_space)
	{
		if (!game->is_shooting)
		{
			game->is_shooting = 1;
			game->shot_anim_frame = 0;
			shoot_laser(game);
		}
	}
	if (key_press == XK_Left)
		game->moves->r_left = true;
	if (key_press == XK_Right)
		game->moves->r_right = true;
	if (key_press == XK_a)
		game->moves->m_left = true;
	if (key_press == XK_d)
		game->moves->m_right = true;
	if (key_press == XK_w)
		game->moves->forward = true;
	if (key_press == XK_s)
		game->moves->backward = true;
	return (0);
}

int	key_release(int key_release, t_game *game)
{
	if (key_release == XK_Escape)
	{
		cleanup_game(game);
		exit(0);
		return (0);
	}
	if (key_release == XK_Left)
		game->moves->r_left = false;
	if (key_release == XK_Right)
		game->moves->r_right = false;
	if (key_release == XK_a)
		game->moves->m_left = false;
	if (key_release == XK_d)
		game->moves->m_right = false;
	if (key_release == XK_w)
		game->moves->forward = false;
	if (key_release == XK_s)
		game->moves->backward = false;
	return (0);
}

static void	move_for_and_backward(double new_x, double new_y, t_game *game)
{
	if (game->moves->forward)
	{
		new_x = game->player.pos_x + game->player.dir_x * 0.05;
		new_y = game->player.pos_y + game->player.dir_y * 0.05;
		if (game->map[(int)game->player.pos_y][(int)(new_x + game->player.dir_x
				* 0.2)] != '1' && game->map[(int)game->player.pos_y][(int)(new_x
				+ game->player.dir_x * 0.2)] != '2' && is_door_passable(game,
				(int)(new_x + game->player.dir_x * 0.2),
				(int)game->player.pos_y))
			game->player.pos_x = new_x;
		if (game->map[(int)(new_y + game->player.dir_y
				* 0.2)][(int)game->player.pos_x] != '1' && game->map[(int)(new_y
				+ game->player.dir_y * 0.2)][(int)game->player.pos_x] != '2'
			&& is_door_passable(game, (int)(new_x + game->player.dir_x * 0.2),
				(int)game->player.pos_y))
			game->player.pos_y = new_y;
	}
	if (game->moves->backward)
	{
		new_x = game->player.pos_x - game->player.dir_x * 0.05;
		new_y = game->player.pos_y - game->player.dir_y * 0.05;
		if (game->map[(int)game->player.pos_y][(int)(new_x - game->player.dir_x
				* 0.2)] != '1' && game->map[(int)game->player.pos_y][(int)(new_x
				- game->player.dir_x * 0.2)] != '2' && is_door_passable(game,
				(int)(new_x + game->player.dir_x * 0.2),
				(int)game->player.pos_y))
			game->player.pos_x = new_x;
		if (game->map[(int)(new_y - game->player.dir_y
				* 0.2)][(int)game->player.pos_x] != '1' && game->map[(int)(new_y
				- game->player.dir_y * 0.2)][(int)game->player.pos_x] != '2'
			&& is_door_passable(game, (int)(new_x + game->player.dir_x * 0.2),
				(int)game->player.pos_y))
			game->player.pos_y = new_y;
	}
}

static void	move_left(double new_x, double new_y, t_game *game)
{
	double	side_x;
	double	side_y;

	if (game->moves->m_left)
	{
		side_x = game->player.dir_y;
		side_y = -game->player.dir_x;
		new_x = game->player.pos_x + side_x * 0.05;
		new_y = game->player.pos_y + side_y * 0.05;
		if (game->map[(int)game->player.pos_y][(int)(new_x + side_x
				* 0.2)] != '1' && game->map[(int)game->player.pos_y][(int)(new_x
				+ side_x * 0.2)] != '2' && is_door_passable(game, (int)(new_x
					+ game->player.dir_x * 0.2), (int)game->player.pos_y))
			game->player.pos_x = new_x;
		if (game->map[(int)(new_y + side_y
				* 0.2)][(int)game->player.pos_x] != '1' && game->map[(int)(new_y
				+ side_y * 0.2)][(int)game->player.pos_x] != '2'
			&& is_door_passable(game, (int)(new_x + game->player.dir_x * 0.2),
				(int)game->player.pos_y))
			game->player.pos_y = new_y;
	}
}

void	move_right(double new_x, double new_y, t_game *game)
{
	double	side_x;
	double	side_y;

	if (game->moves->m_right)
	{
		side_x = -game->player.dir_y;
		side_y = game->player.dir_x;
		new_x = game->player.pos_x + side_x * 0.05;
		new_y = game->player.pos_y + side_y * 0.05;
		if (game->map[(int)game->player.pos_y][(int)(new_x + side_x
				* 0.2)] != '1' && game->map[(int)game->player.pos_y][(int)(new_x
				+ side_x * 0.2)] != '2' && is_door_passable(game, (int)(new_x
					+ game->player.dir_x * 0.2), (int)game->player.pos_y))
			game->player.pos_x = new_x;
		if (game->map[(int)(new_y + side_y
				* 0.2)][(int)game->player.pos_x] != '1' && game->map[(int)(new_y
				+ side_y * 0.2)][(int)game->player.pos_x] != '2'
			&& is_door_passable(game, (int)(new_x + game->player.dir_x * 0.2),
				(int)game->player.pos_y))
			game->player.pos_y = new_y;
	}
}

int	monitor_key(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = 0.0;
	new_y = 0.0;
	move_for_and_backward(new_x, new_y, game);
	move_left(new_x, new_y, game);
	move_right(new_x, new_y, game);
	if (game->moves->r_left)
		rotate(game, -0.05);
	if (game->moves->r_right)
		rotate(game, 0.05);
	return (0);
}
