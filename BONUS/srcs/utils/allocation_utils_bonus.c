/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:22:46 by equintas          #+#    #+#             */
/*   Updated: 2026/06/10 14:52:56 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	*malloc_safe(size_t bytes, char *str)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
		return (NULL);
	}
	return (ret);
}
