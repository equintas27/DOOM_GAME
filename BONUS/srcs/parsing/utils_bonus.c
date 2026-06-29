/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:37:44 by lkingui           #+#    #+#             */
/*   Updated: 2026/06/10 14:58:37 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	*super_malloc(size_t bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (!ptr)
		write(2, "Error: malloc failed\n", 21);
	return (ptr);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (!line || line[0] == '\n' || line[0] == '\0')
		return (0);
	while (line[i])
	{
		if (line[i] != '1'
			&& line[i] != '0'
			&& line[i] != ' '
			&& line[i] != 'N'
			&& line[i] != 'W'
			&& line[i] != 'S'
			&& line[i] != '2'
			&& line[i] != 'D'
			&& line[i] != 'E')
			return (0);
		i++;
	}
	return (1);
}

int	is_first_map_line(char *line)
{
	char	*trimmed;
	int		i;

	i = 0;
	trimmed = ft_strtrim(&line[0], " \n\t");
	if (ft_strncmp(trimmed, "1", 1) != 0)
	{
		free(trimmed);
		return (0);
	}
	free(trimmed);
	return (1);
}

void	print_datas(t_data *data)
{
	write(1, "========textures========\n", 26);
	printf("%s\n", data->north_path);
	printf("%s\n", data->south_path);
	printf("%s\n", data->west_path);
	printf("%s\n", data->east_path);
	write(1, "========colors========\n", 24);
	printf("Floor: r->%d g->%d b->%d\n", data->floor_color->r,
		data->floor_color->g, data->floor_color->b);
	printf("Ceiling: r->%d g->%d b->%d\n", data->ceiling_color->r,
		data->ceiling_color->g, data->ceiling_color->b);
	printf("========RGB Values========\n");
	printf("Floor combined: %d\n", data->floor_color->combined);
	printf("Ceiling combined: %d\n", data->ceiling_color->combined);
}
