/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_u_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:08:42 by ndidenko          #+#    #+#             */
/*   Updated: 2018/05/02 16:08:43 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*ft_u1(char *str, t_parsing *parsing, uintmax_t nbr)
{
	if (nbr == 0 && parsing->precision == 0)
		return (ft_strdup(""));
	else if (nbr == 0)
		return (ft_strdup("0"));
	else
		return (str);
}

static char			*ft_u2(char *str, t_parsing *parsing, int len,
														uintmax_t nbr)
{
	if (parsing->flag_minus == 1)
		return (ft_left(str, parsing->width, len, ' '));
	else if (parsing->flag_zero == 1 && parsing->precision <= 0)
		return (ft_right(str, parsing->width, len, '0'));
	else if (nbr == 0 && parsing->precision == 0)
		return (ft_right(str, parsing->width, 0, ' '));
	else
		return (ft_right(str, parsing->width, len, ' '));
}

static char			*ft_u3(char *str, t_parsing *parsing, int len)
{
	char *tmp;
	char *res;

	if (parsing->flag_minus == 0)
	{
		tmp = ft_right(str, parsing->precision, len, '0');
		res = ft_right(tmp, parsing->width, parsing->precision, ' ');
		ft_strdel(&tmp);
	}
	else
	{
		tmp = ft_right(str, parsing->precision, len, '0');
		res = ft_left(tmp, parsing->width, parsing->precision, ' ');
		ft_strdel(&tmp);
	}
	return (res);
}

static char			*ft_u4(char *str, t_parsing *parsing, int len)
{
	return (ft_right(str, parsing->precision, len, '0'));
}

char				*ft_make_str_u(char *str, t_parsing *parsing, uintmax_t nbr)
{
	char	*res;
	int		len;

	res = 0;
	len = ft_strlen(str);
	if (len >= parsing->width && len > parsing->precision)
		res = ft_u1(str, parsing, nbr);
	else if (len <= parsing->width && len > parsing->precision)
		res = ft_u2(str, parsing, len, nbr);
	else if (len <= parsing->width && len <= parsing->precision &&
		parsing->width >= parsing->precision)
		res = ft_u3(str, parsing, len);
	else if (len <= parsing->precision && parsing->width < parsing->precision)
		res = ft_u4(str, parsing, len);
	return (res);
}
