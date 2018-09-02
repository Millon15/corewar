/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 17:47:30 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/30 21:01:58 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	char	*s1;
	char	*s2;
	size_t	i;

	if (*str2 == '\0')
		return ((char*)str1);
	while (*str1 != '\0' && len > 0)
	{
		if (*str1 == *str2)
		{
			s1 = (char *)str1;
			s2 = (char *)str2;
			i = len;
			while (*s1 && *s2 && *s1 == *s2 && i--)
			{
				s1++;
				s2++;
			}
			if (*s2 == '\0')
				return ((char *)str1);
		}
		len--;
		str1++;
	}
	return (NULL);
}
