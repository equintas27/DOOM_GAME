/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 18:48:05 by lkingui           #+#    #+#             */
/*   Updated: 2026/06/10 14:58:46 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static int	flood_fill(char **map, int x, int y, t_game *game)
{
	if (x < 0 || y < 0)
		return (0);
	if (!map[y] || !map[y][x])
		return (0);
	if (map[y][x] == '1' || map[y][x] == '.')
		return (1);
	if (map[y][x] == ' ' || map[y][x] == '\t')
		return (0);
	map[y][x] = '.';
	if (!flood_fill(map, x, y - 1, game))
		return (0);
	if (!flood_fill(map, x, y + 1, game))
		return (0);
	if (!flood_fill(map, x - 1, y, game))
		return (0);
	if (!flood_fill(map, x + 1, y, game))
		return (0);
	return (1);
}

static void	print_map(char **map)
{
	int	i;

	i = 0;
	write(1, "\n========map========\n", 22);
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

static int	check_flood_fill_result_aux(char **map_copy, int i, int j)
{
	if (map_copy[i][j] != '1' && map_copy[i][j] != '.')
	{
		write(2, "Error\nInvalid path\n", 20);
		print_map(map_copy);
		free_map(map_copy);
		return (0);
	}
	return (1);
}

int	check_flood_fill_result(t_game *game)
{
	char	**map_copy;
	int		i;
	int		j;

	i = 0;
	map_copy = copy_map(game->map);
	if (!flood_fill(map_copy, game->pos_x, game->pos_y, game))
		return (write(2, "Error\nOpened map!\n", 19), free_map(map_copy), 0);
	while (map_copy[i])
	{
		j = 0;
		while (map_copy[i][j])
		{
			if (map_copy[i][j] == ' ' || map_copy[i][j] == '\t')
			{
				j++;
				continue ;
			}
			if (!check_flood_fill_result_aux(map_copy, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (free_map(map_copy), 1);
}
