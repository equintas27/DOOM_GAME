/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkingui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:43:17 by lkingui           #+#    #+#             */
/*   Updated: 2025/06/13 14:44:28 by lkingui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d_len;
	size_t	s_len;
	size_t	i;

	if (!dst || !src)
		return (ft_strlen(dst) + ft_strlen(src));
	d_len = 0;
	s_len = 0;
	i = 0;
	while (d_len < dstsize && dst[d_len] != '\0')
		d_len++;
	while (src[s_len] != '\0')
		s_len++;
	if (dstsize <= d_len)
		return (dstsize + s_len);
	while (src[i] != '\0' && (d_len + i) < (dstsize - 1))
	{
		dst[d_len + i] = src[i];
		i++;
	}
	dst[d_len + i] = '\0';
	return (d_len + s_len);
}
