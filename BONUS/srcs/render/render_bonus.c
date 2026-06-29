/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 17:04:47 by equintas          #+#    #+#             */
/*   Updated: 2026/06/29 10:50:01 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				my_mlx_put_img(game->img, x, y,
					game->data->ceiling_color->combined);
			else
				my_mlx_put_img(game->img, x, y,
					game->data->floor_color->combined);
			x++;
		}
		y++;
	}
}

void	get_enemy_position(t_game *game, char enemy_char)
{
	char	*img_buffer;
	int		y;
	int		x;

	img_buffer = game->enemy_img->addr;
	if (!img_buffer)
	{
		cleanup_game(game);
		exit(1);
	}
	y = 0;
	game->enemy_count = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == enemy_char)
			{
				game->enemies[game->enemy_count].x = x;
				game->enemies[game->enemy_count].y = y;
				game->enemy_count++;
			}
			x++;
		}
		y++;
	}
}

void	put_figures(t_game *game)
{
	char	*img_buffer;
	int		i;

	i = 0;
	while (i < game->enemy_count)
	{
		game->enemies[i].enemy_pos_x = game->enemies[i].x + 0.5;
		game->enemies[i].enemy_pos_y = game->enemies[i].y + 0.5;
		draw_enemies(game, i);
		i++;
	}
	img_buffer = game->gamer_img->addr;
	if (!img_buffer)
	{
		cleanup_game(game);
		exit(1);
	}
	if (game->is_shooting)
		shoot_laser(game);
	draw_weapon(game);
}

int	render_frame(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	monitor_key(game);
	draw_background(game);
	update_door_animation(game);
	raycasting(game);
	put_figures(game);
	draw_minimap(game);
	draw_direction(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img_ptr, 0, 0);
	return (0);
}
