/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 18:37:04 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/24 18:57:12 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	if (s != 0 && f != 0)
	{
		len = ft_strlen(s);
		while (len > i)
			(*f)(i++, s++);
	}
}
