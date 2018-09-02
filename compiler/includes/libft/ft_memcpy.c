/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 17:47:35 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/29 21:45:48 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char			*dest2;
	const char		*src2;
	unsigned int	i;

	dest2 = (char*)dest;
	src2 = (char*)src;
	i = 0;
	while (n)
	{
		dest2[i] = src2[i];
		i++;
		n--;
	}
	return (dest);
}
