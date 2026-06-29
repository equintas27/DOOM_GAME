/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks3_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 17:46:25 by lkingui           #+#    #+#             */
/*   Updated: 2026/06/22 09:30:50 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	check_number_of_players(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N')
				game->n_player++;
			else if (game->map[i][j] == 'E')
				game->n_player++;
			else if (game->map[i][j] == 'W')
				game->n_player++;
			else if (game->map[i][j] == 'S')
				game->n_player++;
			j++;
		}
		i++;
	}
}

int	check_map_content(t_game *game)
{
	check_number_of_players(game);
	if (game->n_player == 0)
	{
		write(2, "Error\nMust have a player\n", 26);
		return (0);
	}
	else if (game->n_player > 1)
	{
		write(2, "Error\nMust have only one player\n", 33);
		return (0);
	}
	return (1);
}

static int	map_position_aux(int count, char **file)
{
	if (count >= 0 && ft_isempty_line(file[count]))
	{
		while (count >= 0 && ft_isempty_line(file[count]))
			count--;
		if (count >= 0 && is_map_line(file[count]))
			return (1);
	}
	return (0);
}

int	is_map_at_middle_or_top(char **file, char *file_name)
{
	int	fd;
	int	count;
	int	old_count;

	fd = open(file_name, O_RDONLY);
	count = count_lines(fd) - 1;
	old_count = count;
	close(fd);
	while (count >= 0 && file[count] && ft_isempty_line(file[count]))
		count--;
	while (count >= 0 && file[count] && is_map_line(file[count])
		&& !ft_isempty_line(file[count]))
		count--;
	if (map_position_aux(count, file))
		return (1);
	count = old_count;
	while (count >= 0 && file[count] && ft_isempty_line(file[count]))
		count--;
	if (count < 0 || !is_map_line(file[count]))
		return (1);
	return (0);
}

int	check_map_chars(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0'
			&& map[i][j] != 'E' && map[i][j] != 'N'
			&& map[i][j] != 'S' && map[i][j] != 'W'
			&& map[i][j] != '2' && map[i][j] != 'D'
			&& map[i][j] != '\t' && map[i][j] != ' ')
			{
				write(2, "Error\nThe map contains invalid char\n", 37);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
