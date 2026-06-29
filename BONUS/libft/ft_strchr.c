/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stcrhr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkingui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:56:29 by lkingui           #+#    #+#             */
/*   Updated: 2025/06/10 13:46:06 by lkingui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			p;

	if (!s)
		return (NULL);
	p = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == p)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == p)
		return ((char *) &s[i]);
	return (NULL);
}
