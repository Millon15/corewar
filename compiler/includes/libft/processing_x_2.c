/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_x_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:09:32 by ndidenko          #+#    #+#             */
/*   Updated: 2018/05/02 16:09:33 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_x2_2(char *str, t_parsing *parsing, int len, uintmax_t nbr)
{
	char *res;
	char *tmp;

	if (parsing->flag_minus == 1)
	{
		tmp = ft_strjoin("0x", str);
		res = ft_left(tmp, parsing->width, len + 2, ' ');
	}
	else if (nbr == 0)
	{
		tmp = ft_right(str, len, len, '0');
		res = ft_right(tmp, parsing->width, ft_strlen(tmp), ' ');
	}
	else
	{
		tmp = ft_strjoin("0x", str);
		res = ft_right(tmp, parsing->width, len + 2, ' ');
	}
	ft_strdel(&tmp);
	return (res);
}

char			*ft_x2(char *str, t_parsing *parsing, int len, uintmax_t nbr)
{
	char *res;
	char *tmp;

	if (parsing->flag_minus == 1 && parsing->flag_sharp == 0)
		res = ft_left(str, parsing->width, len, ' ');
	else if (parsing->flag_zero == 1 && parsing->precision <= 0 &&
			parsing->flag_minus == 0 && parsing->flag_sharp == 1)
	{
		tmp = ft_right(str, parsing->width - 2, len, '0');
		res = ft_strjoin("0x", tmp);
		ft_strdel(&tmp);
	}
	else if (parsing->flag_zero == 1 && parsing->precision <= 0 &&
		parsing->flag_minus == 0 && parsing->flag_sharp == 0)
		res = ft_right(str, parsing->width, len, '0');
	else if (parsing->flag_sharp == 1)
		res = ft_x2_2(str, parsing, len, nbr);
	else if (nbr == 0 && parsing->precision <= 0)
		res = ft_right(str, parsing->width, 0, ' ');
	else
		res = ft_right(str, parsing->width, len, ' ');
	return (res);
}
