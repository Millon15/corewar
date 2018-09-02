/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_max.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 15:57:30 by ndidenko          #+#    #+#             */
/*   Updated: 2018/05/02 15:57:31 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		len_nbr(uintmax_t n, int c)
{
	size_t			len;

	len = 0;
	if (n == 0)
		return (1);
	if (c == 1)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char				*ft_itoa_max(intmax_t n)
{
	size_t			len;
	int				c;
	char			*str;
	uintmax_t		un;

	c = 0;
	if (n < 0)
	{
		c = 1;
		un = -1 * n;
	}
	else
		un = n;
	len = len_nbr(un, c);
	if (!(str = ft_strnew(len)))
		return (0);
	while (len)
	{
		str[len - 1] = (un % 10) + 48;
		un = un / 10;
		len--;
	}
	if (c == 1)
		str[0] = '-';
	return (str);
}

static size_t		len_nbr_base(uintmax_t n, int base)
{
	size_t len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / base;
		len++;
	}
	return (len);
}

char				*ft_itoa_base(uintmax_t n, int base)
{
	int		len;
	char	*str;

	len = len_nbr_base(n, base);
	str = ft_strnew(len);
	if (!str)
		return (0);
	while (len)
	{
		if (n % base >= 10)
			str[len - 1] = (n % base - 10) + 'a';
		else
			str[len - 1] = (n % base) + '0';
		n = n / base;
		len--;
	}
	return (str);
}
