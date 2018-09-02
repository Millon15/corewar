/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_x_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:09:14 by ndidenko          #+#    #+#             */
/*   Updated: 2018/05/02 16:09:15 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_x1(char *str, t_parsing *parsing, uintmax_t nbr)
{
	char *res;

	if (parsing->flag_sharp == 1 && nbr != 0)
	{
		res = ft_strjoin("0x", str);
		free(str);
	}
	else if (nbr == 0 && parsing->precision >= 0)
		res = ft_strdup("");
	else
		res = str;
	return (res);
}

static char		*ft_x4(char *str, t_parsing *parsing, int len, uintmax_t nbr)
{
	char *res;
	char *tmp;

	if (parsing->flag_sharp == 1 && nbr != 0)
	{
		res = ft_right(str, parsing->precision, len, '0');
		tmp = res;
		res = ft_strjoin("0x", tmp);
		free(tmp);
	}
	else
		res = ft_right(str, parsing->precision, len, '0');
	return (res);
}

char			*ft_make_str_x(char *str, t_parsing *parsing, uintmax_t nbr)
{
	char	*res;
	int		len;

	res = 0;
	len = ft_strlen(str);
	if (len >= parsing->width && len > parsing->precision)
		res = ft_x1(str, parsing, nbr);
	else if (len <= parsing->width && len > parsing->precision)
		res = ft_x2(str, parsing, len, nbr);
	else if (len <= parsing->width && len <= parsing->precision &&
		parsing->width >= parsing->precision)
		res = ft_x3(str, parsing, len);
	else if (len <= parsing->precision && parsing->width < parsing->precision)
		res = ft_x4(str, parsing, len, nbr);
	return (res);
}
