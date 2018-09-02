/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_x.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:08:59 by ndidenko          #+#    #+#             */
/*   Updated: 2018/05/02 16:09:00 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static uintmax_t	ft_cast_x(t_parsing *parsing, va_list ap)
{
	uintmax_t	nbr;

	if (parsing->size == 4)
		nbr = va_arg(ap, uintmax_t);
	else if (parsing->size == 3)
		nbr = va_arg(ap, unsigned long long);
	else if (parsing->size == 2 || parsing->size == 5)
		nbr = va_arg(ap, unsigned long);
	else if (parsing->size == 1)
		nbr = (unsigned short)va_arg(ap, unsigned int);
	else if (parsing->size == 0)
		nbr = (unsigned char)va_arg(ap, unsigned int);
	else
		nbr = va_arg(ap, unsigned int);
	return (nbr);
}

static char			*ft_strtoupper(char *str)
{
	char *new;
	char *ptr;

	new = ft_strnew(ft_strlen(str));
	ptr = new;
	while (*str)
	{
		if (*str >= 'a' && *str <= 'z')
			*new = *str - 32;
		else
			*new = *str;
		new++;
		str++;
	}
	return (ptr);
}

static void			processing_x_2(t_parsing *parsing, char *str)
{
	ft_putstr(str);
	parsing->len += ft_strlen(str);
}

void				processing_x(t_parsing *parsing, va_list ap)
{
	uintmax_t	nbr;
	char		*str;
	size_t		len;
	char		*tmp;

	nbr = ft_cast_x(parsing, ap);
	str = ft_itoa_base(nbr, 16);
	len = ft_strlen(str);
	if (parsing->width == -1 && parsing->precision == -1 &&
		parsing->flag_zero == 0 && parsing->flag_minus == 0
		&& parsing->flag_sharp == 0 && parsing->letter != 'X' && nbr != 0)
		processing_x_2(parsing, str);
	else
	{
		str = ft_make_str_x(str, parsing, nbr);
		if (parsing->letter == 'X')
		{
			tmp = str;
			str = ft_strtoupper(str);
			free(tmp);
		}
		ft_putstr(str);
		parsing->len += ft_strlen(str);
	}
	free(str);
}
