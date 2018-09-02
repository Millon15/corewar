/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 18:48:28 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/30 15:48:31 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	i;
	char	*result;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
		{
			result = (char*)&str[i];
			return (result);
		}
		i++;
	}
	if (str[i] == (char)c)
	{
		result = (char*)&str[i];
		return (result);
	}
	return (0);
}
