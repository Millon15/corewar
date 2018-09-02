/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 19:15:24 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/30 15:51:17 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
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
		newstr[i] = (*f)(newstr[i]);
		i++;
	}
	return (newstr);
}
