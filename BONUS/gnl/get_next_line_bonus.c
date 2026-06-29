/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:11:19 by lkingui           #+#    #+#             */
/*   Updated: 2026/06/10 15:00:26 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static char	*clean_stash(char *stash)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] != '\n')
	{
		free(stash);
		return (NULL);
	}
	i++;
	new = malloc(ft_strlen(stash + i) + 1);
	if (!new)
		return (NULL);
	while (stash[i])
		new [j++] = stash[i++];
	new[j] = '\0';
	free(stash);
	return (new);
}

static int	read_to_stash(int fd, char **stash)
{
	char	*buffer;
	int		b_read;
	char	*tmp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	b_read = 1;
	while (b_read > 0 && !ft_strchr(*stash, '\n'))
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read < 0)
		{
			free(buffer);
			return (-1);
		}
		buffer[b_read] = '\0';
		tmp = *stash;
		*stash = ft_strjoin(tmp, buffer);
		free(tmp);
		if (!*stash)
			break ;
	}
	free(buffer);
	return (b_read);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;
	ssize_t		n;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	n = read_to_stash(fd, &stash);
	if (n < 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	if (!stash || !*stash)
		return (free(stash), stash = NULL, NULL);
	line = extract_line(stash);
	stash = clean_stash(stash);
	return (line);
}
