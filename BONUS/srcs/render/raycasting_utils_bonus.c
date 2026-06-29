/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 13:43:01 by equintas          #+#    #+#             */
/*   Updated: 2026/06/29 10:47:04 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	calcul_perp_wall_dist(t_raycast *vars)
{
	if (vars->side == 0)
		vars->perp_wall_dist = vars->side_dist_x - vars->delta_dist_x;
	else
		vars->perp_wall_dist = vars->side_dist_y - vars->delta_dist_y;
}

int	verify_side(t_raycast *vars)
{
	int	tex_num;

	tex_num = 0;
	if (vars->side == 0)
	{
		if (vars->ray_dir_x > 0)
			tex_num = 2;
		else
			tex_num = 3;
	}
	else if (vars->side == 1)
	{
		if (vars->ray_dir_y < 0)
			tex_num = 0;
		else
			tex_num = 1;
	}
	return (tex_num);
}

int	get_texture_color(t_game *game, int tex_num, int tex_x, double tex_pos)
{
	int	tex_y;
	int	offset;
	int	color;

	tex_y = (int)tex_pos;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= game->text[tex_num].height)
		tex_y = game->text[tex_num].height - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= game->text[tex_num].width)
	{
		tex_x = game->text[tex_num].width - 1;
	}
	offset = ((tex_y * game->text[tex_num].line_len) + (tex_x
				* game->text[tex_num].bits_per_pixel / 8));
	color = *(int *)(game->text[tex_num].addr + offset);
	return (color);
}

void	calcul_texture_vars(t_game *game, t_raycast *vars)
{
	double	wall_x;
	int		openning;

	vars->tex_num = verify_side(vars);
	if (vars->is_door)
		vars->tex_num = 4;
	if (vars->side == 0)
		wall_x = game->player.pos_y + (vars->perp_wall_dist * vars->ray_dir_y);
	else
		wall_x = game->player.pos_x + (vars->perp_wall_dist * vars->ray_dir_x);
	wall_x -= floor(wall_x);
	vars->tex_x = (int)(wall_x * (double)game->text[vars->tex_num].width);
	if (vars->is_door)
	{
		openning = abs(game->door_frame[vars->map_pos_y][vars->map_pos_x]);
		vars->tex_x += openning * (game->text[vars->tex_num].width / 8);
		if (vars->tex_x >= game->text[vars->tex_num].width)
			vars->tex_x = game->text[vars->tex_num].width - 1;
	}
	if ((vars->side == 0 && vars->ray_dir_x < 0) || (vars->side == 1
			&& vars->ray_dir_y > 0))
		vars->tex_x = game->text[vars->tex_num].width - vars->tex_x - 1;
	vars->step = 1.0 * game->text[vars->tex_num].height / vars->line_height;
	vars->tex_pos = (vars->draw_start - HEIGHT / 2.0 + vars->line_height / 2.0)
		* vars->step;
}

void	verify_tex_y(int *tex_y, int tex_height)
{
	if (*tex_y < 0)
		*tex_y = 0;
	else if (*tex_y >= tex_height)
		*tex_y = tex_height - 1;
}
