/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:07:07 by ndidenko          #+#    #+#             */
/*   Updated: 2018/05/02 16:07:08 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*make_str_s0(t_parsing *parsing, char *str, int len)
{
	if (parsing->width == len && parsing->precision == len)
		return (str);
	else if (parsing->width <= len && parsing->precision >= len)
		return (str);
	else if (parsing->width <= len && parsing->precision <= len)
		return (ft_right(str, parsing->precision, parsing->precision, '0'));
	else if (parsing->width > len && (parsing->precision >= len ||
													parsing->precision == 0))
		return (ft_right(str, parsing->width, len, '0'));
	else if (parsing->width > len && parsing->precision < len)
		return (ft_left(str, parsing->width, parsing->precision, '0'));
	else
		return (str);
}

static char		*make_str_s1(t_parsing *parsing, char *str, int len)
{
	if (parsing->width == len && parsing->precision == len)
		return (str);
	if (parsing->width <= len && parsing->precision >= len)
		return (str);
	else if (parsing->width <= len && parsing->precision <= len)
		return (ft_left(str, parsing->precision, parsing->precision, ' '));
	else if (parsing->width > len && (parsing->precision >= len ||
													parsing->precision <= 0))
		return (ft_left(str, parsing->width, len, ' '));
	else if (parsing->width > len && parsing->precision < len)
		return (ft_left(str, parsing->width, parsing->precision, ' '));
	else
		return (str);
}

static char		*make_str_s2(t_parsing *parsing, char *str, int len)
{
	if (parsing->width == len && parsing->precision == len)
		return (str);
	else if (parsing->width <= len && parsing->precision >= len)
		return (str);
	else if (parsing->width > 0 && parsing->precision == 0)
		return (ft_right(str, parsing->width, 0, ' '));
	else if (parsing->width <= 0 && parsing->precision <= len)
		return (ft_right(str, parsing->precision, parsing->precision, ' '));
	else if (parsing->width <= len && parsing->precision <= len
				&& parsing->width > parsing->precision)
		return (ft_right(str, parsing->width, parsing->precision, ' '));
	else if (parsing->width <= len && parsing->precision <= len)
		return (ft_right(str, parsing->precision, parsing->precision, ' '));
	else if (parsing->width > len && (parsing->precision >= len ||
													parsing->precision <= 0))
		return (ft_right(str, parsing->width, len, ' '));
	else if (parsing->width > len && parsing->precision < len)
		return (ft_right(str, parsing->width, parsing->precision, ' '));
	else
		return (str);
}

void			processing_s(t_parsing *parsing, va_list ap)
{
	char	*str;
	int		len;

	str = (char*)va_arg(ap, char*);
	if (str == 0)
		str = "(null)";
	len = ft_strlen(str);
	if (parsing->width < 0 && parsing->precision < 0)
	{
		ft_putstr(str);
		parsing->len += len;
	}
	else
	{
		if (parsing->flag_minus == 1)
			str = make_str_s1(parsing, str, len);
		else if (parsing->flag_zero == 1)
			str = make_str_s0(parsing, str, len);
		else
			str = make_str_s2(parsing, str, len);
		len = ft_strlen(str);
		ft_putstr(str);
		parsing->len += len;
	}
}
