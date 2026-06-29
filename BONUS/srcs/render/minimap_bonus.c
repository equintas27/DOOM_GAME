/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 15:30:00 by lkingui           #+#    #+#             */
/*   Updated: 2026/06/17 13:41:02 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 15)
	{
		j = 0;
		while (j < 15)
		{
			my_mlx_put_img(game->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			my_mlx_put_img(game->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_direction(t_game *game)
{
	int	i;
	int	x;
	int	y;
	int	start_x;
	int	start_y;

	start_x = 15 + game->player.pos_x * 15 + 7;
	start_y = 15 + game->player.pos_y * 15 + 7;
	i = 0;
	while (i < 30)
	{
		x = start_x + game->player.dir_x * i;
		y = start_y + game->player.dir_y * i;
		my_mlx_put_img(game->img, x, y, 0xFF0000);
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				draw_square(game, 15 + x * 15, 15 + y * 15, 0xFFFFFF);
			if (game->map[y][x] == 'N' || game->map[y][x] == 'W'
				|| game->map[y][x] == 'S' || game->map[y][x] == 'E')
				draw_player(game, 15 + game->player.pos_x * 15, 15
					+ game->player.pos_y * 15, 0xFF0000);
			x++;
		}
		y++;
	}
}

void	d_move_player(t_game *game, double dx, double dy)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + dx;
	new_y = game->player.pos_y + dy;
	if (game->map[(int)new_y][(int)new_x + 1] == '1'
		|| game->map[(int)new_y][(int)new_x + 1] == '2')
		return ;
	game->player.pos_x = new_x;
	game->player.pos_y = new_y;
	draw_minimap(game);
}
