/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 17:01:38 by lkingui           #+#    #+#             */
/*   Updated: 2026/06/10 14:54:46 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	ac_check(int ac, t_game *game)
{
	if (ac != 2)
	{
		write(2, "Error\nUsage: <./cub3D> <map_path>\n", 36);
		free_map(game->map);
		exit(1);
	}
	return (1);
}

int	extension(char *file)
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
		if (file[i + 1] == 'c' && file[i + 2] == 'u' && file[i + 3] == 'b')
			return (1);
		else
			return (0);
		i++;
	}
	return (1);
}

void	check_extension(char *file)
{
	if (!extension(file))
	{
		write(2, "Error\nThe file extension must be .cub!\n", 40);
		exit(1);
	}
}

int	ft_isempty_line(char *line)
{
	if (!line)
		return (1);
	while (*line)
	{
		if (*line != ' ' && *line != '\t')
			return (0);
		line++;
	}
	return (1);
}
