/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 19:55:05 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/30 15:53:18 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			i;
	char			*newstr;
	size_t			len;

	if (f == 0 || s == 0)
		return (0);
	i = 0;
	len = ft_strlen(s);
	newstr = ft_memalloc(len + 1);
	if (newstr == 0)
		return (0);
	ft_strcpy(newstr, s);
	while (newstr[i])
	{
		newstr[i] = (*f)(i, newstr[i]);
		i++;
	}
	return (newstr);
}
