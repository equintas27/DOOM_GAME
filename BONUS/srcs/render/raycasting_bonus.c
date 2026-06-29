/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:06:38 by equintas          #+#    #+#             */
/*   Updated: 2026/06/29 10:46:34 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static int	apply_shading(int color, double dist)
{
	double	factor;
	int		r;
	int		g;
	int		b;

	factor = 1.0 - (dist / 15.0);
	if (factor < 0.3)
		factor = 0.3;
	if (factor > 1.0)
		factor = 1.0;
	r = ((color >> 16) & 0xFF) * factor;
	g = ((color >> 8) & 0xFF) * factor;
	b = (color & 0xFF) * factor;
	return ((r << 16) | (g << 8) | b);
}

void	find_fov(t_game *game, t_raycast *vars)
{
	vars->camera_x = 2.0 * (vars->x / (double)WIDTH) - 1.0;
	vars->ray_dir_x = game->player.dir_x + game->player.plane_x
		* vars->camera_x;
	vars->ray_dir_y = game->player.dir_y + game->player.plane_y
		* vars->camera_x;
	if (vars->ray_dir_x == 0)
		vars->delta_dist_x = 1e30;
	else
		vars->delta_dist_x = fabs(1.0 / vars->ray_dir_x);
	if (vars->ray_dir_y == 0)
		vars->delta_dist_y = 1e30;
	else
		vars->delta_dist_y = fabs(1.0 / vars->ray_dir_y);
	vars->map_pos_x = (int)game->player.pos_x;
	vars->map_pos_y = (int)game->player.pos_y;
}

void	def_ray(t_game *game, t_raycast *vars)
{
	if (vars->ray_dir_x > 0)
	{
		vars->side_dist_x = (vars->map_pos_x + 1 - game->player.pos_x)
			* vars->delta_dist_x;
		vars->step_x = 1;
	}
	else
	{
		vars->side_dist_x = (game->player.pos_x - vars->map_pos_x)
			* vars->delta_dist_x;
		vars->step_x = -1;
	}
	if (vars->ray_dir_y > 0)
	{
		vars->side_dist_y = (vars->map_pos_y + 1 - game->player.pos_y)
			* vars->delta_dist_y;
		vars->step_y = 1;
	}
	else
	{
		vars->side_dist_y = (game->player.pos_y - vars->map_pos_y)
			* vars->delta_dist_y;
		vars->step_y = -1;
	}
}

void	aux_rayscasting(t_game *game, t_raycast *vars)
{
	while (!vars->hit)
	{
		if (vars->side_dist_x < vars->side_dist_y)
		{
			vars->side_dist_x += vars->delta_dist_x;
			vars->map_pos_x += vars->step_x;
			vars->side = 0;
		}
		else
		{
			vars->side_dist_y += vars->delta_dist_y;
			vars->map_pos_y += vars->step_y;
			vars->side = 1;
		}
		if (vars->map_pos_x < 0 || vars->map_pos_y < 0)
		{
			vars->hit = 1;
			break ;
		}
		if (game->map[vars->map_pos_y][vars->map_pos_x] == '1')
			vars->hit = 1;
		else if (game->map[vars->map_pos_y][vars->map_pos_x] == 'D'
			&& abs(game->door_frame[vars->map_pos_y][vars->map_pos_x]) < 6)
		{
			vars->hit = 1;
			vars->is_door = 1;
		}
	}
	calcul_perp_wall_dist(vars);
}

void	design_wall(t_raycast *vars, t_game *game)
{
	int	tex_y;

	if (vars->perp_wall_dist <= 0)
		vars->perp_wall_dist = 0.1;
	else if (vars->perp_wall_dist > 100.0)
		return ;
	vars->line_height = (int)(HEIGHT / vars->perp_wall_dist);
	vars->draw_start = ((HEIGHT / 2) - vars->line_height / 2);
	if (vars->draw_start < 0)
		vars->draw_start = 0;
	vars->draw_end = ((HEIGHT / 2) + vars->line_height / 2);
	if (vars->draw_end >= HEIGHT)
		vars->draw_end = HEIGHT - 1;
	calcul_texture_vars(game, vars);
	vars->y = vars->draw_start;
	while (vars->y <= vars->draw_end)
	{
		tex_y = (int)vars->tex_pos;
		verify_tex_y(&tex_y, game->text[vars->tex_num].height);
		vars->color = get_texture_color(game, vars->tex_num, vars->tex_x,
				tex_y);
		vars->color = apply_shading(vars->color, vars->perp_wall_dist);
		my_mlx_put_img(game->img, vars->x, vars->y, vars->color);
		vars->tex_pos += vars->step;
		vars->y++;
	}
}

void	raycasting(t_game *game)
{
	t_raycast	vars;

	ft_bzero(&vars, sizeof(t_raycast));
	vars.x = 0;
	while (vars.x < WIDTH)
	{
		vars.hit = 0;
		vars.is_door = 0;
		find_fov(game, &vars);
		def_ray(game, &vars);
		aux_rayscasting(game, &vars);
		game->zbuffer[vars.x] = vars.perp_wall_dist;
		design_wall(&vars, game);
		vars.x++;
	}
}
