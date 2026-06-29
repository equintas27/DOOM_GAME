/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks5_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 17:46:40 by lkingui           #+#    #+#             */
/*   Updated: 2026/06/10 14:58:48 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	check_texture_extension(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	while (i > 0 && file[i] != '.')
		i--;
	if (file[i + 4])
		return (0);
	while (file[i])
	{
		if (file[i - 1] == '/' || !file[i - 1])
			return (0);
		if (file[i + 1] == 'x' && file[i + 2] == 'p' && file[i + 3] == 'm')
			return (1);
		else
			return (0);
		i++;
	}
	return (1);
}

void	check_textures_extension(t_data *data, t_game *game, char **file)
{
	(void)data;
	(void)file;
	if (!data->north_path || !data->south_path || !data->west_path
		|| !data->east_path)
	{
		write(2, "Error\nMissing texture(s)\n", 26);
		cleanup_game(game);
		exit(1);
	}
	if (!check_texture_extension(data->north_path)
		|| !check_texture_extension(data->south_path)
		|| !check_texture_extension(data->west_path)
		|| !check_texture_extension(data->east_path))
	{
		write(2, "Error\nInvalid Texture extension\n", 33);
		cleanup_game(game);
		exit(1);
	}
}

int	check_invalid_lines_in_file(t_game *game, char *trimmed, int i)
{
	if (ft_strncmp(trimmed, "NO", 2) != 0 && ft_strncmp(trimmed, "SO", 2) != 0
		&& ft_strncmp(trimmed, "WE", 2) != 0 && ft_strncmp(trimmed, "EA",
			2) != 0 && ft_strncmp(trimmed, "F", 1) != 0 && ft_strncmp(trimmed,
			"C", 1) != 0 && !is_map_line(game->file[i]))
		return (0);
	return (1);
}

void	check_all_file_lines(t_game *game, t_data *data)
{
	int		i;
	char	*trimmed;

	(void)data;
	i = 0;
	while (game->file[i])
	{
		if (ft_isempty_line(game->file[i]))
		{
			i++;
			continue ;
		}
		trimmed = ft_strtrim(game->file[i], " \t");
		if (!check_invalid_lines_in_file(game, trimmed, i))
		{
			write(2, "Error\nInvalid line in file\n", 28);
			cleanup_game(game);
			free(trimmed);
			exit(1);
		}
		free(trimmed);
		i++;
	}
}
