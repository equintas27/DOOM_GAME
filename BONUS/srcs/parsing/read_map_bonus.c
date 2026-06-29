/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 17:07:11 by lkingui           #+#    #+#             */
/*   Updated: 2026/06/10 14:58:39 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static char	**fill_map(int fd, char **map)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		map[count++] = line;
		line = get_next_line(fd);
	}
	map[count] = NULL;
	return (map);
}

char	**read_map(char	*file)
{
	int		fd;
	int		count;
	char	**map;

	count = 0;
	if (!extension(file))
		error_msg();
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_msg();
	count = count_lines(fd);
	close(fd);
	map = malloc(sizeof(char *) * (count + 1));
	if (!map)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_msg();
	map = fill_map(fd, map);
	close(fd);
	return (map);
}
