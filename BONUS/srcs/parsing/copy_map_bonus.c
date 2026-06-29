/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:54:55 by lkingui           #+#    #+#             */
/*   Updated: 2026/06/10 14:55:39 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

char	*copy_line(char *line)
{
	int		i;
	int		len;
	char	*new_line;

	i = 0;
	len = 0;
	while (line[len])
		len++;
	new_line = malloc(len + 1);
	if (!new_line)
		return (NULL);
	while (i < len)
	{
		new_line[i] = line[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

void	*free_copy(char **copy, int y)
{
	int	i;

	i = 0;
	while (i < y)
	{
		if (copy[i])
			free(copy[i]);
		i++;
	}
	free(copy);
	return (NULL);
}

char	**copy_map(char **map)
{
	int		y;
	int		i;
	char	**copy;

	y = 0;
	while (map[y] && !ft_isempty_line(map[y]))
		y++;
	copy = malloc(sizeof(char *) * (y + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < y)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
			return (free_copy(copy, i));
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
