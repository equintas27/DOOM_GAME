/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_datas_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 13:54:20 by lkingui           #+#    #+#             */
/*   Updated: 2026/06/10 14:58:43 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	init_floor_colors(t_game *game, char **file, t_data *data)
{
	int		i;
	int		j;
	char	**splited;

	i = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == ' ' || file[i][j] == '\t')
			j++;
		if (ft_strncmp(file[i] + j, "F", 1) == 0)
		{
			data->count_floor_colors++;
			data->floor_color_pos = i;
			splited = ft_split(file[i] + j + 1, ',');
			check_valid_datas(splited, game, data, file);
			data->floor_color->r = ft_atoi(splited[0]);
			data->floor_color->g = ft_atoi(splited[1]);
			data->floor_color->b = ft_atoi(splited[2]);
			data->floor_color->combined = (data->floor_color->r << 16)
				| (data->floor_color->g << 8) | data->floor_color->b;
			free_split(splited);
		}
		i++;
	}
}

void	init_ceiling_colors(t_game *game, char **file, t_data *data)
{
	int		i;
	int		j;
	char	**splited;

	i = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == ' ' || file[i][j] == '\t')
			j++;
		if (ft_strncmp(file[i] + j, "C", 1) == 0)
		{
			data->count_ceiling_colors++;
			data->ceiling_color_pos = i;
			splited = ft_split(file[i] + j + 1, ',');
			check_valid_datas(splited, game, data, file);
			data->ceiling_color->r = ft_atoi(splited[0]);
			data->ceiling_color->g = ft_atoi(splited[1]);
			data->ceiling_color->b = ft_atoi(splited[2]);
			data->ceiling_color->combined = (data->ceiling_color->r << 16)
				| (data->ceiling_color->g << 8) | data->ceiling_color->b;
			free_split(splited);
		}
		i++;
	}
}

void	init_textures_aux(t_data **data, t_game *game, int i, int j)
{
	if (ft_strncmp(game->file[i] + j, "WE", 2) == 0)
	{
		if ((*data)->west_path)
			free((*data)->west_path);
		(*data)->west_path = ft_strtrim(game->file[i] + j + 2, " \n\t");
		(*data)->count_textures++;
		check_invalid_texture_separation(data, game, i);
	}
	else if (ft_strncmp(game->file[i] + j, "EA", 2) == 0)
	{
		if ((*data)->east_path)
			free((*data)->east_path);
		(*data)->east_path = ft_strtrim(game->file[i] + j + 2, " \n\t");
		(*data)->count_textures++;
		check_invalid_texture_separation(data, game, i);
	}
}

void	init_textures(t_data **data, t_game *game, int i, int j)
{
	if (ft_strncmp(game->file[i] + j, "NO", 2) == 0)
	{
		if ((*data)->north_path)
			free((*data)->north_path);
		(*data)->north_path = ft_strtrim(game->file[i] + j + 2, " \n\t");
		(*data)->count_textures++;
		check_invalid_texture_separation(data, game, i);
	}
	else if (ft_strncmp(game->file[i] + j, "SO", 2) == 0)
	{
		if ((*data)->south_path)
			free((*data)->south_path);
		(*data)->south_path = ft_strtrim(game->file[i] + j + 2, " \n\t");
		(*data)->count_textures++;
		check_invalid_texture_separation(data, game, i);
	}
	init_textures_aux(data, game, i, j);
}
