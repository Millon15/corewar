/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 17:19:32 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/17 17:51:44 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char		*dstnew;
	const char	*srcnew;
	size_t		n;
	size_t		len;

	dstnew = dst;
	srcnew = src;
	n = dstsize;
	while (n-- != 0 && *dstnew != '\0')
		dstnew++;
	len = dstnew - dst;
	n = dstsize - len;
	if (n == 0)
		return (len + ft_strlen(srcnew));
	while (*srcnew != '\0')
	{
		if (n != 1)
		{
			*dstnew++ = *srcnew;
			n--;
		}
		srcnew++;
	}
	*dstnew = '\0';
	return (len + (srcnew - src));
}
