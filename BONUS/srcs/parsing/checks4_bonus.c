/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks4_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 17:46:32 by lkingui           #+#    #+#             */
/*   Updated: 2026/06/10 14:58:51 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	validate_rgb(char **splited)
{
	int	i;
	int	j;

	i = 0;
	while (splited[i])
	{
		j = 0;
		while (splited[i][j])
		{
			if (!splited[0] || !splited[1] || !splited[2])
				return (0);
			while (splited[i][j] == ' ' || splited[i][j] == '\t')
				j++;
			if (!ft_isdigit(splited[i][j]) || (splited[i][j] == '-'
					&& !ft_isdigit(splited[i][j + 1])) || (splited[i][j] == '+'
					&& !ft_isdigit(splited[i][j + 1])))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	check_limit_rgb(t_data *data, t_game *game, char **file)
{
	(void)data;
	(void)file;
	if ((data->floor_color->r < 0 || data->floor_color->r > 255)
		|| (data->floor_color->g < 0 || data->floor_color->g > 255)
		|| (data->floor_color->b < 0 || data->floor_color->b > 255)
		|| (data->ceiling_color->r < 0 || data->ceiling_color->r > 255)
		|| (data->ceiling_color->g < 0 || data->ceiling_color->g > 255)
		|| (data->ceiling_color->b < 0 || data->ceiling_color->b > 255))
	{
		write(2, "Error\nRGB value out of bounds\n", 30);
		cleanup_game(game);
		exit(1);
	}
}

void	check_valid_datas(char **splited, t_game *game, t_data *data,
		char **file)
{
	(void)file;
	(void)data;
	if (!validate_rgb(splited))
	{
		printf("Error\nInvalid RGB value\n");
		cleanup_game(game);
		free_split(splited);
		exit(1);
	}
}

void	check_invalid_colors_separation(t_data *data, char **file, t_game *game)
{
	int	last;

	last = data->ceiling_color_pos;
	if (data->floor_color_pos > last)
		last = data->floor_color_pos;
	if (data->ceiling_color_pos < data->floor_color_pos
		&& ft_isempty_line(file[data->ceiling_color_pos + 1]))
	{
		write(2, "Error\nInvalid element separation\n", 34);
		cleanup_game(game);
		exit(1);
	}
	if (data->floor_color_pos < data->ceiling_color_pos
		&& ft_isempty_line(file[data->floor_color_pos + 1]))
	{
		write(2, "Error\nInvalid element separation\n", 34);
		cleanup_game(game);
		exit(1);
	}
	if (file[last + 1] && !ft_isempty_line(file[last + 1]))
	{
		write(2, "Error\nInvalid element separation\n", 34);
		cleanup_game(game);
		exit(1);
	}
}

void	check_invalid_texture_separation(t_data **data, t_game *game, int i)
{
	if (((*data)->count_textures == 4 && !ft_isempty_line(game->file[i + 1]))
		|| ((*data)->count_textures != 4 && ft_isempty_line(game->file[i + 1])))
	{
		write(2, "Error\nElements must be separated by at least one line\n",
			55);
		cleanup_game(game);
		exit(1);
	}
}
