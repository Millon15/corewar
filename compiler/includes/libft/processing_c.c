/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:05:21 by ndidenko          #+#    #+#             */
/*   Updated: 2018/05/02 16:05:22 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		processing_c_0(int width)
{
	int i;

	i = width;
	while (i != 1)
	{
		write(1, " ", 1);
		i--;
	}
	write(1, "\0", 1);
	return (width);
}

static int		processing_c_0zero(int width)
{
	int i;

	i = width;
	while (i != 1)
	{
		write(1, "0", 1);
		i--;
	}
	write(1, "\0", 1);
	return (width);
}

void			processing_c(t_parsing *parsing, va_list ap)
{
	char c;
	char *res;

	c = (char)va_arg(ap, int);
	if (parsing->width > 0 && c != 0)
	{
		if (parsing->flag_minus == 1)
			res = ft_left(&c, parsing->width, 1, ' ');
		else if (parsing->flag_minus == 0)
			res = ft_right(&c, parsing->width, 1, ' ');
		ft_putstr(res);
		parsing->len += ft_strlen(res);
	}
	else if (parsing->width > 0 && c == 0 && parsing->flag_zero == 0)
		parsing->len += processing_c_0(parsing->width);
	else if (parsing->width > 0 && c == 0 && parsing->flag_zero == 1)
		parsing->len += processing_c_0zero(parsing->width);
	else
	{
		ft_putchar(c);
		parsing->len += 1;
	}
}
