/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 20:42:45 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/29 21:50:14 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*src2;
	unsigned char	*dest2;
	size_t			i;

	i = 0;
	src2 = (unsigned char*)src;
	dest2 = (unsigned char*)dest;
	if (dest2 > src2)
		while (n)
		{
			i = n - 1;
			dest2[i] = src2[i];
			n--;
		}
	else
		while (i < n)
		{
			dest2[i] = src2[i];
			i++;
		}
	return (dest2);
}
