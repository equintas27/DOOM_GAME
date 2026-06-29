/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkingui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:25:35 by lkingui           #+#    #+#             */
/*   Updated: 2025/06/16 11:58:32 by lkingui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char			cc;
	unsigned char			*cs;
	size_t					i;

	if (!s)
		return (NULL);
	cc = (unsigned char)c;
	cs = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (cs[i] == cc)
			return ((void *) &cs[i]);
		i++;
	}
	return (NULL);
}
