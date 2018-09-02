/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:33:26 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/15 17:12:08 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	char	*array;
	size_t	i;

	array = (char*)destination;
	i = 0;
	while (n)
	{
		array[i++] = c;
		n--;
	}
	return (destination);
}
