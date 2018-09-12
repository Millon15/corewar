/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:33:26 by ndidenko          #+#    #+#             */
/*   Updated: 2018/09/12 05:08:13 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	char	*array;
	size_t	i;

	array = (unsigned char *)destination;
	i = 0;
	while (n)
	{
		array[i++] = c;
		n--;
	}
	return (destination);
}
