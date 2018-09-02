/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 19:39:25 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/29 21:49:33 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t size)
{
	size_t			i;
	unsigned char	*src2;
	unsigned char	*dest2;

	src2 = (unsigned char *)src;
	dest2 = (unsigned char *)dest;
	i = 0;
	while (size)
	{
		dest2[i] = src2[i];
		if (src2[i] == (unsigned char)c)
			return (dest + (i + 1));
		i++;
		size--;
	}
	return (NULL);
}
