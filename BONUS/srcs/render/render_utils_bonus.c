/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:15:52 by equintas          #+#    #+#             */
/*   Updated: 2026/06/29 10:50:31 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	my_mlx_put_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_tex_color(t_img *img, int x, int y)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(int *)pixel);
}

static int	pseudo_noise(int seed)
{
	seed = (seed << 13) ^ seed;
	return (((seed * (seed * seed * 15731 + 789221) + 1376312589) & 0x7fffffff)
		% 7 - 3);
}

static void	draw_bolt(t_game *game, t_weapon_vars *vars)
{
	vars->center_x = WIDTH / 2;
	vars->start_y = HEIGHT / 2;
	vars->end_y = HEIGHT - 160;
	vars->current_y = vars->end_y;
	vars->noise_x = 0;
	while (vars->current_y > vars->start_y)
	{
		if (vars->current_y % 6 == 0)
			vars->noise_x = pseudo_noise(vars->current_y + game->shot_anim_frame
					* 17);
		vars->local_cx = vars->center_x + vars->noise_x;
		vars->thickness = 1 + (vars->end_y - vars->current_y) * 3 / (vars->end_y
				- vars->start_y);
		vars->x_offset = -vars->thickness;
		while (vars->x_offset <= vars->thickness)
		{
			vars->current_x = vars->local_cx + vars->x_offset;
			if (vars->current_x >= 0 && vars->current_x < WIDTH
				&& vars->current_y >= 0 && vars->current_y < HEIGHT)
			{
				vars->dist = abs(vars->x_offset);
				if (vars->dist == 0)
					my_mlx_put_img(game->img, vars->current_x, vars->current_y,
						0xFFFFFF);
				else if (vars->dist <= vars->thickness / 3 + 1)
					my_mlx_put_img(game->img, vars->current_x, vars->current_y,
						0xD8B8FF);
				else if (vars->dist <= vars->thickness * 2 / 3 + 1)
					my_mlx_put_img(game->img, vars->current_x, vars->current_y,
						0x9A4DFF);
				else
					my_mlx_put_img(game->img, vars->current_x, vars->current_y,
						0x3A0070);
			}
			vars->x_offset++;
		}
		vars->current_y--;
	}
}

static void	draw_impact_flash(t_game *game, t_weapon_vars *vars)
{
	if (game->shot_anim_frame >= 4)
		return ;
	vars->size = 10;
	vars->s_y = -vars->size;
	while (vars->s_y <= vars->size)
	{
		vars->s_x = -vars->size;
		while (vars->s_x <= vars->size)
		{
			if (abs(vars->s_x) + abs(vars->s_y) < vars->size && vars->center_x
				+ vars->s_x >= 0 && vars->center_x + vars->s_x < WIDTH
				&& vars->start_y + vars->s_y >= 0 && vars->start_y
				+ vars->s_y < HEIGHT)
				my_mlx_put_img(game->img, vars->center_x + vars->s_x,
					vars->start_y + vars->s_y, 0xFFFFFF);
			vars->s_x++;
		}
		vars->s_y++;
	}
}

static void	draw_gamer_sprite(t_game *game, t_weapon_vars *vars)
{
	vars->y = 0;
	while (vars->y < 300)
	{
		vars->x = 0;
		while (vars->x < 300)
		{
			vars->color = get_tex_color(game->gamer_img, vars->x, vars->y);
			if (vars->color != -16777216)
				my_mlx_put_img(game->img, WIDTH / 2 - 300 / 2 + vars->x, HEIGHT
					- 300 + vars->y, vars->color);
			vars->x++;
		}
		vars->y++;
	}
}

void	draw_weapon(t_game *game)
{
	t_weapon_vars	vars;

	if (game->is_shooting == 1)
	{
		draw_bolt(game, &vars);
		draw_impact_flash(game, &vars);
		game->shot_anim_frame++;
		if (game->shot_anim_frame >= 8)
			game->is_shooting = 0;
	}
	draw_gamer_sprite(game, &vars);
}

void	get_enemies_formulas(t_game *game, double *enemy_x, double *enemy_y,
		int i)
{
	int	v_move_screen;

	game->enemies[i].visible = 1;
	(*enemy_x) = game->enemies[i].enemy_pos_x - game->player.pos_x;
	(*enemy_y) = game->enemies[i].enemy_pos_y - game->player.pos_y;
	game->enemies[i].det = game->player.plane_x * game->player.dir_y
		- game->player.dir_x * game->player.plane_y;
	game->enemies[i].transform_x = (game->player.dir_y * (*enemy_x)
			- game->player.dir_x * (*enemy_y)) / game->enemies[i].det;
	game->enemies[i].transform_y = (game->player.plane_x * (*enemy_y)
			- game->player.plane_y * (*enemy_x)) / game->enemies[i].det;
	if (game->enemies[i].transform_y <= 0)
	{
		game->enemies[i].visible = 0;
		return ;
	}
	v_move_screen = (int)(200.0 / game->enemies[i].transform_y);
	game->enemies[i].sprite_screen_x = (WIDTH / 2) * (1
			+ game->enemies[i].transform_x / game->enemies[i].transform_y);
	// tamanho baseado na distância
	game->enemies[i].sprite_h = abs((int)(HEIGHT
				/ game->enemies[i].transform_y));
	game->enemies[i].sprite_w = game->enemies[i].sprite_h;
	game->enemies[i].draw_start_y = -game->enemies[i].sprite_h / 2 + HEIGHT / 2
		+ v_move_screen;
	game->enemies[i].draw_end_y = game->enemies[i].sprite_h / 2 + HEIGHT / 2
		+ v_move_screen;
	game->enemies[i].draw_start_x = -game->enemies[i].sprite_w / 2
		+ game->enemies[i].sprite_screen_x;
	game->enemies[i].draw_end_x = game->enemies[i].sprite_w / 2
		+ game->enemies[i].sprite_screen_x;
}

void	draw_enemies(t_game *game, int i)
{
	double	enemy_x;
	double	enemy_y;
	int		x;
	int		y;
	int		tex_x;
	int		tex_y;
	int		start_x;
	int		end_x;
	int		start_y;
	int		end_y;

	get_enemies_formulas(game, &enemy_x, &enemy_y, i);
	if (!game->enemies[i].visible)
		return ;
	// Limites clampados para o loop (não alteram os originais)
	start_x = game->enemies[i].draw_start_x;
	end_x = game->enemies[i].draw_end_x;
	start_y = game->enemies[i].draw_start_y;
	end_y = game->enemies[i].draw_end_y;
	if (start_x < 0)
		start_x = 0;
	if (end_x >= WIDTH)
		end_x = WIDTH - 1;
	if (start_y < 0)
		start_y = 0;
	if (end_y >= HEIGHT)
		end_y = HEIGHT - 1;
	x = start_x;
	while (x < end_x)
	{
		// tex_x usa draw_start_x ORIGINAL para mapear corretamente
		tex_x = (x - game->enemies[i].draw_start_x) * game->enemies[i].width
			/ game->enemies[i].sprite_w;
		if (x >= 0 && x < WIDTH
			&& game->enemies[i].transform_y < game->zbuffer[x])
		{
			y = start_y;
			while (y < end_y)
			{
				// tex_y usa draw_start_y ORIGINAL
				tex_y = (y - game->enemies[i].draw_start_y)
					* game->enemies[i].height / game->enemies[i].sprite_h;
				game->enemies[i].color = get_tex_color(game->enemy_img, tex_x,
						tex_y);
				if (game->enemies[i].color != -16777216)
					my_mlx_put_img(game->img, x, y, game->enemies[i].color);
				y++;
			}
		}
		x++;
	}
}
