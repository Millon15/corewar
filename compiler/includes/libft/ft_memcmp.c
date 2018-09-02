/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:51:47 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/18 17:06:17 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *array1, const void *array2, size_t n)
{
	unsigned const char *ac1;
	unsigned const char *ac2;

	ac1 = (unsigned const char*)array1;
	ac2 = (unsigned const char*)array2;
	while (n != 0)
	{
		if (*ac1 != *ac2)
			return (*ac1 - *ac2);
		ac1++;
		ac2++;
		n--;
	}
	return (0);
}
