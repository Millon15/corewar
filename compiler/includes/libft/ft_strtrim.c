/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 17:15:46 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/27 16:06:16 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v'
			|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

char		*ft_strtrim(char const *s)
{
	char	*str;
	int		len;
	size_t	i;
	int		j;

	if (s == 0)
		return (0);
	i = 0;
	j = 0;
	len = ft_strlen(s);
	while (ft_isspace(s[len - 1]))
		len--;
	while (ft_isspace(s[i]))
	{
		len--;
		i++;
	}
	len = (len < 0) ? 0 : len;
	if ((str = (char *)malloc(sizeof(char) * (len + 1))) == 0)
		return (0);
	while (j < len)
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}
