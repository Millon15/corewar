/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 19:09:22 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/30 15:53:53 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	i;
	char	*result;

	i = 0;
	result = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
		{
			result = (char*)&str[i];
		}
		i++;
	}
	if (str[i] == (char)c)
	{
		result = (char*)&str[i];
	}
	return (result);
}
