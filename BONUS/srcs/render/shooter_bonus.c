/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shooter_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 13:43:40 by equintas          #+#    #+#             */
/*   Updated: 2026/06/29 11:45:38 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	init_vars(t_shooter_vars *vars, t_game *game)
{
	vars->ray_pos_x = game->player.pos_x;
	vars->ray_pos_y = game->player.pos_y;
	vars->ray_dir_x = game->player.dir_x;
	vars->ray_dir_y = game->player.dir_y;
	vars->map_x = (int)vars->ray_pos_x;
	vars->map_y = (int)vars->ray_pos_y;
	vars->delta_dist_x = fabs(1 / vars->ray_dir_x);
	vars->delta_dist_y = fabs(1 / vars->ray_dir_y);
	vars->hit = 0;
}

static void	def_dir(t_shooter_vars *vars)
{
	if (vars->ray_dir_x < 0)
	{
		vars->step_x = -1;
		vars->side_dist_x = (vars->ray_pos_x - vars->map_x)
			* vars->delta_dist_x;
	}
	else
	{
		vars->step_x = 1;
		vars->side_dist_x = (vars->map_x + 1.0 - vars->ray_pos_x)
			* vars->delta_dist_x;
	}
	if (vars->ray_dir_y < 0)
	{
		vars->step_y = -1;
		vars->side_dist_y = (vars->ray_pos_y - vars->map_y)
			* vars->delta_dist_y;
	}
	else
	{
		vars->step_y = 1;
		vars->side_dist_y = (vars->map_y + 1.0 - vars->ray_pos_y)
			* vars->delta_dist_y;
	}
}

static void	loop_of_hit(t_shooter_vars *vars, t_game *game)
{
	while (!vars->hit)
	{
		if (vars->side_dist_x < vars->side_dist_y)
		{
			vars->side_dist_x += vars->delta_dist_x;
			vars->map_x += vars->step_x;
		}
		else
		{
			vars->side_dist_y += vars->delta_dist_y;
			vars->map_y += vars->step_y;
		}
		if (game->map[vars->map_y][vars->map_x] == '2')
			vars->hit = 2;
		else if (game->map[vars->map_y][vars->map_x] == '1'
			|| game->map[vars->map_y][vars->map_x] == 'D')
			vars->hit = 1;
	}
}

void	shoot_laser(t_game *game)
{
	t_shooter_vars	vars;

	ft_bzero(&vars, sizeof(t_shooter_vars));
	init_vars(&vars, game);
	def_dir(&vars);
	loop_of_hit(&vars, game);
	if (vars.hit == 2)
		printf("Inimigo acertado\n");
}
