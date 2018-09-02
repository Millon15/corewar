/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 21:00:39 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/15 21:09:39 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *copyto, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (n && src[i])
	{
		copyto[i] = src[i];
		i++;
		n--;
	}
	while (n)
	{
		copyto[i] = '\0';
		i++;
		n--;
	}
	return (copyto);
}
