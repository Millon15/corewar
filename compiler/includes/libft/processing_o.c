/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_o.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:06:30 by ndidenko          #+#    #+#             */
/*   Updated: 2018/05/02 16:06:31 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static uintmax_t	ft_cast_o(t_parsing *parsing, va_list ap)
{
	uintmax_t	nbr;

	if (parsing->size == 4 && parsing->letter != 'O')
		nbr = va_arg(ap, uintmax_t);
	else if (parsing->size == 3 && parsing->letter != 'O')
		nbr = va_arg(ap, unsigned long long);
	else if (parsing->size == 2 || parsing->size == 5 || parsing->letter == 'O')
		nbr = va_arg(ap, unsigned long);
	else if (parsing->size == 1 && parsing->letter != 'O')
		nbr = (unsigned short)va_arg(ap, unsigned int);
	else if (parsing->size == 0 && parsing->letter != 'O')
		nbr = (unsigned char)va_arg(ap, unsigned int);
	else
		nbr = va_arg(ap, unsigned int);
	return (nbr);
}

void				processing_o(t_parsing *parsing, va_list ap)
{
	uintmax_t	nbr;
	char		*str;
	size_t		len;

	nbr = ft_cast_o(parsing, ap);
	str = ft_itoa_base(nbr, 8);
	len = ft_strlen(str);
	if (parsing->width == -1 && parsing->precision == -1 &&
		parsing->flag_zero == 0 && parsing->flag_minus == 0
		&& parsing->flag_sharp == 0 && nbr != 0)
	{
		ft_putstr(str);
		parsing->len += len;
	}
	else
	{
		str = ft_make_str_o(str, parsing, nbr);
		ft_putstr(str);
		parsing->len += ft_strlen(str);
	}
	free(str);
}
