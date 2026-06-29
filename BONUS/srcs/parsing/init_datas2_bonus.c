/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_datas2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:00:33 by lkingui           #+#    #+#             */
/*   Updated: 2026/06/22 11:25:10 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	init_data_struct(t_data **data)
{
	(*data) = super_malloc(sizeof(t_data));
	(*data)->north_path = NULL;
	(*data)->south_path = NULL;
	(*data)->west_path = NULL;
	(*data)->east_path = NULL;
	(*data)->ceiling_color = super_malloc(sizeof(t_color));
	(*data)->floor_color = super_malloc(sizeof(t_color));
	(*data)->ceiling_color->r = 0;
	(*data)->ceiling_color->g = 0;
	(*data)->ceiling_color->b = 0;
	(*data)->floor_color->r = 0;
	(*data)->floor_color->g = 0;
	(*data)->floor_color->b = 0;
	(*data)->floor_color->combined = 0;
	(*data)->ceiling_color->combined = 0;
	(*data)->count_floor_colors = 0;
	(*data)->count_ceiling_colors = 0;
	(*data)->count_textures = 0;
	(*data)->floor_color_pos = 0;
	(*data)->ceiling_color_pos = 0;
}

void	init_data(t_game *game, t_data **data)
{
	int	j;
	int	i;

	init_data_struct(data);
	i = 0;
	while (game->file[i])
	{
		j = 0;
		while (game->file[i][j] == ' ' || game->file[i][j] == '\t')
			j++;
		init_textures(data, game, i, j);
		i++;
	}
	game->is_shooting = 0;
	game->shot_anim_frame = 0;
	init_ceiling_colors(game, game->file, *data);
	init_floor_colors(game, game->file, *data);
	check_invalid_colors_separation(*data, game->file, game);
	check_colors_number(*data, game);
	check_textures_number(*data, game);
	check_limit_rgb(*data, game, game->file);
	check_textures_extension(*data, game, game->file);
}
