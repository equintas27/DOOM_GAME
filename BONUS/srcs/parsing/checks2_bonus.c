/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 17:46:16 by lkingui           #+#    #+#             */
/*   Updated: 2026/06/10 14:54:52 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	check_colors_number(t_data *data, t_game *game)
{
	if (data->count_ceiling_colors > 1 || data->count_floor_colors > 1)
	{
		write(2, "Error\nDoubles were found\n", 26);
		cleanup_game(game);
		exit(1);
	}
	if ((data->count_floor_colors == 1 && data->count_ceiling_colors == 0)
		|| (data->count_floor_colors == 0 && data->count_ceiling_colors == 1))
	{
		write(2, "Error\nMust have 2 colors\n", 26);
		cleanup_game(game);
		exit(1);
	}
	if (data->count_ceiling_colors == 0 && data->count_floor_colors == 0)
	{
		write(2, "Error\nNo colors were found\n", 28);
		cleanup_game(game);
		exit(1);
	}
}

void	check_textures_number(t_data *data, t_game *game)
{
	if (data->count_textures > 4)
	{
		write(2, "Error\nDoubles were found\n", 26);
		cleanup_game(game);
		exit(1);
	}
	if (data->count_textures == 0)
	{
		write(2, "Error\nNo textures were found\n", 30);
		cleanup_game(game);
		exit(1);
	}
}
