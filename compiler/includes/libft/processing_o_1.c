/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_o_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:06:39 by ndidenko          #+#    #+#             */
/*   Updated: 2018/05/02 16:06:40 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_o1(char *str, t_parsing *parsing, int len, uintmax_t nbr)
{
	if (parsing->flag_sharp == 1 && nbr == 0)
		return (ft_strdup("0"));
	else if (nbr == 0 && parsing->precision >= 0)
		return (ft_strdup(""));
	else if (parsing->flag_sharp == 1 && nbr != 0)
		return (ft_right(str, len + 1, len, '0'));
	else
		return (str);
}

static char		*ft_o2_2(char *str, t_parsing *parsing, int len, uintmax_t nbr)
{
	char *tmp;
	char *res;

	if (parsing->flag_minus == 1)
	{
		tmp = ft_right(str, len + 1, len, '0');
		res = ft_left(tmp, parsing->width, ft_strlen(tmp), ' ');
		ft_strdel(&tmp);
	}
	else if (nbr == 0)
	{
		tmp = ft_right(str, len, len, '0');
		res = ft_right(tmp, parsing->width, ft_strlen(tmp), ' ');
		ft_strdel(&tmp);
	}
	else
	{
		tmp = ft_right(str, len + 1, len, '0');
		res = ft_right(tmp, parsing->width, ft_strlen(tmp), ' ');
		ft_strdel(&tmp);
	}
	return (res);
}

static char		*ft_o2(char *str, t_parsing *parsing, int len, uintmax_t nbr)
{
	if (parsing->flag_sharp == 1)
		return (ft_o2_2(str, parsing, len, nbr));
	else if (parsing->flag_minus == 1 && parsing->flag_sharp == 0)
		return (ft_left(str, parsing->width, len, ' '));
	else if (parsing->flag_zero == 1 && parsing->precision <= 0)
		return (ft_right(str, parsing->width, len, '0'));
	else if (nbr == 0 && parsing->precision == 0)
		return (ft_right(str, parsing->width, 0, ' '));
	else
		return (ft_right(str, parsing->width, len, ' '));
}

static char		*ft_o3(char *str, t_parsing *parsing, int len)
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

char			*ft_make_str_o(char *str, t_parsing *parsing, uintmax_t nbr)
{
	char	*res;
	int		len;

	res = 0;
	len = ft_strlen(str);
	if (len >= parsing->width && len > parsing->precision)
		res = ft_o1(str, parsing, len, nbr);
	else if (len <= parsing->width && len > parsing->precision)
		res = ft_o2(str, parsing, len, nbr);
	else if (len <= parsing->width && len <= parsing->precision &&
		parsing->width >= parsing->precision)
		res = ft_o3(str, parsing, len);
	else if (len <= parsing->precision && parsing->width < parsing->precision)
		res = ft_right(str, parsing->precision, len, '0');
	return (res);
}
