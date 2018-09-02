/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:04:51 by ndidenko          #+#    #+#             */
/*   Updated: 2018/05/02 16:04:52 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_left(char *str, int width, int precision, char c)
{
	char	*snew;
	int		i;

	i = 0;
	snew = ft_strnew(width);
	while (i < width)
	{
		if (i < precision)
			snew[i] = str[i];
		else
			snew[i] = c;
		i++;
	}
	return (snew);
}

char	*ft_right(char *str, int width, int precision, char c)
{
	char	*snew;
	int		i;
	int		j;
	int		len_c;

	i = 0;
	j = 0;
	len_c = width - precision;
	snew = ft_strnew(width);
	while (i < width)
	{
		if (i < len_c)
			snew[i] = c;
		else
			snew[i] = str[j++];
		i++;
	}
	return (snew);
}
