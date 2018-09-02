/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_d_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:06:05 by ndidenko          #+#    #+#             */
/*   Updated: 2018/05/02 16:06:07 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_d2(char *str, t_parsing *parsing, int len, intmax_t nbr)
{
	char *res;

	if (parsing->flag_minus == 1)
	{
		res = ft_left(str, parsing->width, len, ' ');
		free(str);
	}
	else if ((parsing->flag_zero == 1 && nbr < 0) ||
	(parsing->flag_zero == 1 && parsing->flag_plus == 1 && nbr < 0))
	{
		res = ft_right(++str, parsing->width + 1, len, '0');
		res[0] = '-';
	}
	else if (parsing->flag_zero == 1 && parsing->flag_plus == 1 && nbr >= 0)
	{
		res = ft_right(str, parsing->width, len, '0');
		res[0] = '+';
	}
	else
	{
		res = ft_d2_2(str, parsing, len, nbr);
		free(str);
	}
	return (res);
}

char		*ft_d2_2(char *str, t_parsing *parsing, int len, intmax_t nbr)
{
	char	*res;
	char	*tmp;

	if (parsing->flag_zero == 1 && nbr >= 0 && parsing->precision <= 0 &&
		parsing->flag_space == 0)
		res = ft_right(str, parsing->width, len, '0');
	else if (parsing->flag_zero == 1 && nbr >= 0 && parsing->precision < 0 &&
		parsing->flag_space == 1)
	{
		res = ft_right(str, parsing->width, len, '0');
		res[0] = ' ';
	}
	else if (nbr == 0 && parsing->precision == 0)
		res = ft_right(str, parsing->width, 0, ' ');
	else if (parsing->flag_plus == 1)
	{
		tmp = ft_right(str, len + 1, len, ' ');
		tmp[0] = '+';
		res = ft_right(tmp, parsing->width, len + 1, ' ');
	}
	else
		res = ft_right(str, parsing->width, len, ' ');
	return (res);
}

char		*ft_d3(char *str, t_parsing *parsing, int len, intmax_t nbr)
{
	char *res;
	char *tmp;

	if (parsing->flag_minus == 0 && nbr < 0)
	{
		tmp = ft_right(++str, parsing->precision + 2, len, '0');
		tmp[0] = '-';
		res = ft_right(tmp, parsing->width, parsing->precision + 1, ' ');
	}
	else if (parsing->flag_minus == 1 && nbr < 0)
	{
		tmp = ft_right(++str, parsing->precision + 2, len, '0');
		tmp[0] = '-';
		res = ft_left(tmp, parsing->width, parsing->precision + 1, ' ');
	}
	else if ((parsing->flag_plus == 1) || (parsing->flag_minus == 1))
		res = ft_d3_1(str, parsing, len);
	else
	{
		tmp = ft_right(str, parsing->precision, len, '0');
		res = ft_right(tmp, parsing->width, parsing->precision, ' ');
		free(str);
	}
	ft_strdel(&tmp);
	return (res);
}

char		*ft_d3_1(char *str, t_parsing *parsing, int len)
{
	char *res;
	char *tmp;

	res = 0;
	if (parsing->flag_minus == 1 && parsing->flag_plus == 1)
	{
		tmp = ft_right(str, parsing->precision + 1, len, '0');
		tmp[0] = '+';
		res = ft_left(tmp, parsing->width, parsing->precision + 1, ' ');
	}
	else if (parsing->flag_plus == 1)
	{
		tmp = ft_right(str, parsing->precision + 1, len, '0');
		tmp[0] = '+';
		res = ft_right(tmp, parsing->width, parsing->precision + 1, ' ');
	}
	else if (parsing->flag_minus == 1)
	{
		tmp = ft_right(str, parsing->precision, len, '0');
		res = ft_left(tmp, parsing->width, parsing->precision, ' ');
	}
	ft_strdel(&tmp);
	return (res);
}

char		*ft_d4(char *str, t_parsing *parsing, int len, intmax_t nbr)
{
	char *res;

	if (parsing->flag_plus == 1)
	{
		res = ft_right(str, parsing->precision + 1, len, '0');
		res[0] = '+';
	}
	else if (nbr < 0 && parsing->precision >= parsing->width)
	{
		res = ft_right(str + 1, parsing->precision + 2, len, '0');
		res[0] = '-';
	}
	else if (parsing->flag_space == 1)
	{
		res = ft_right(str, parsing->precision + 1, len, '0');
		res[0] = ' ';
	}
	else
		res = ft_right(str, parsing->precision, len, '0');
	return (res);
}
