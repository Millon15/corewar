/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:06:49 by ndidenko          #+#    #+#             */
/*   Updated: 2018/05/02 16:06:50 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_make_str_p2(char *str, t_parsing *parsing, int len,
														uintmax_t nbr)
{
	char *res;
	char *tmp;

	if (parsing->width < len && len < parsing->precision)
		res = ft_strjoin("0x", ft_right(str, parsing->precision, len, '0'));
	else if (parsing->width > 0 && parsing->precision == 0 && nbr == 0)
		res = ft_right(ft_strjoin("0x", str), parsing->width, len + 2, ' ');
	else if (parsing->precision == 0 && parsing->width <= 0 && nbr == 0)
		res = ft_strjoin("0x", ft_strdup(""));
	else if (parsing->width >= parsing->precision &&
		parsing->precision > 0 && nbr == 0)
	{
		tmp = ft_strjoin("0x", ft_right(str, parsing->precision, 0, '0'));
		res = ft_right(tmp, parsing->width, parsing->precision + 2, ' ');
		ft_strdel(&tmp);
	}
	else
		res = ft_strjoin("0x", str);
	return (res);
}

static char		*ft_make_str_p(char *str, t_parsing *parsing, int len,
														uintmax_t nbr)
{
	char *res;

	if (parsing->precision == -1 && parsing->width <= 0 && nbr == 0)
		res = ft_strjoin("0x", ft_strdup("0"));
	else if (parsing->precision > 0 && parsing->width <= 0 && nbr == 0)
		res = ft_strjoin("0x", ft_right(str, parsing->precision, 0, '0'));
	else if (parsing->width > 0 && parsing->flag_zero == 1 &&
						parsing->flag_minus == 0 && nbr == 0)
		res = ft_strjoin("0x", ft_right(str, parsing->width - 2, 1, '0'));
	else if (parsing->width > len && len > parsing->precision
				&& parsing->flag_minus == 0)
		res = ft_right(ft_strjoin("0x", str), parsing->width, len + 2, ' ');
	else if (parsing->width > len && len > parsing->precision
				&& parsing->flag_minus == 1)
	{
		res = ft_strjoin("0x", str);
		if (len + 2 < parsing->width)
			res = ft_left(res, parsing->width, len + 2, ' ');
	}
	else
	{
		res = ft_make_str_p2(str, parsing, len, nbr);
		free(str);
	}
	return (res);
}

void			processing_p(t_parsing *parsing, va_list ap)
{
	uintmax_t	nbr;
	char		*str;
	int			len;

	nbr = va_arg(ap, unsigned long long);
	str = ft_itoa_base(nbr, 16);
	len = ft_strlen(str);
	str = ft_make_str_p(str, parsing, len, nbr);
	ft_putstr(str);
	parsing->len += ft_strlen(str);
	free(str);
}
