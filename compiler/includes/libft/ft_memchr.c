/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 22:15:07 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/29 21:53:03 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*pointer;
	unsigned char	cbuff;
	size_t			i;

	i = 0;
	pointer = (unsigned char *)s;
	cbuff = (unsigned char)c;
	while (n != 0)
	{
		if (pointer[i] == cbuff)
		{
			return (pointer + i);
		}
		i++;
		n--;
	}
	return (0);
}
