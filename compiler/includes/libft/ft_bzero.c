/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 17:32:45 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/15 17:39:43 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *destination, size_t n)
{
	char		*array;
	size_t		i;

	array = (char*)destination;
	i = 0;
	while (n)
	{
		array[i++] = 0;
		n--;
	}
}
