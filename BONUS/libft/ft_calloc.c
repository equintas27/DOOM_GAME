/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkingui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:11:00 by lkingui           #+#    #+#             */
/*   Updated: 2025/06/17 11:46:40 by lkingui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;
	size_t			i;
	size_t			total;

	i = 0;
	total = count * size;
	if (count == 0 || size == 0)
		return (malloc(0));
	if (total / count != size)
		return (NULL);
	tmp = malloc(total);
	if (!tmp)
		return (NULL);
	while (i < total)
		tmp[i++] = 0;
	return (tmp);
}
