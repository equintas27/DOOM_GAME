/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkingui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:35:31 by lkingui           #+#    #+#             */
/*   Updated: 2025/06/16 13:25:34 by lkingui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char			*cs1;
	const unsigned char			*cs2;	
	size_t						i;

	if (n == 0)
		return (0);
	cs1 = (const unsigned char *)s1;
	cs2 = (const unsigned char *)s2;
	if (!cs1 && !cs2)
		return (0);
	if (!cs1)
		return (-*cs2);
	if (!cs2)
		return (*cs1);
	i = 0;
	while (i < n)
	{
		if (cs1[i] != cs2[i])
			return (cs1[i] - cs2[i]);
		i++;
	}
	return (0);
}
