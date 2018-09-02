/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_unicode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:08:50 by ndidenko          #+#    #+#             */
/*   Updated: 2018/05/02 16:08:51 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_make_unicode(wchar_t n, t_parsing *parsing)
{
	char *s;

	s = ft_strnew(4);
	if (n <= ft_2to10("01111111") || (MB_CUR_MAX == 1))
		*s = n;
	else if (n <= ft_2to10("011111111111"))
	{
		s[0] = (n >> 6) | ft_2to10("11000000");
		s[1] = (n & ft_2to10("00111111")) | ft_2to10("10000000");
	}
	else if (n <= ft_2to10("1111111111111111"))
	{
		s[0] = (n >> 12) | ft_2to10("11100000");
		s[1] = ((n >> 6) & ft_2to10("00111111")) | ft_2to10("10000000");
		s[2] = (n & ft_2to10("00111111")) | ft_2to10("10000000");
	}
	else
	{
		s[0] = (n >> 18) | ft_2to10("11110000");
		s[1] = ((n >> 12) & ft_2to10("00111111")) | ft_2to10("10000000");
		s[2] = ((n >> 6) & ft_2to10("00111111")) | ft_2to10("10000000");
		s[3] = (n & ft_2to10("00111111")) | ft_2to10("10000000");
	}
	parsing->len += ft_strlen(s);
	return (s);
}

static char		*ft_make_str_unicode(t_parsing *parsing, wchar_t *uni_str,
														wchar_t uni_char)
{
	char *str;
	char *tmp;
	char *tmp2;

	str = ft_strdup("");
	if (parsing->letter == 'S' || (parsing->size == 2 &&
								parsing->letter == 's'))
	{
		while (*uni_str)
		{
			tmp = ft_make_unicode(*uni_str, parsing);
			tmp2 = str;
			str = ft_strjoin(str, tmp);
			uni_str++;
			free(tmp);
			free(tmp2);
		}
	}
	else
	{
		tmp = str;
		str = ft_make_unicode(uni_char, parsing);
		free(tmp);
	}
	return (str);
}

static char		*ft_width_unicode(t_parsing *parsing, char *str)
{
	char *res;

	if (parsing->width > parsing->len && parsing->flag_zero == 0
		&& parsing->flag_minus == 0 && parsing->precision <= 0)
		res = ft_right(str, parsing->width, parsing->len, ' ');
	else if (parsing->width > parsing->len && parsing->flag_zero == 1
		&& parsing->flag_minus == 0 && parsing->precision <= 0)
		res = ft_right(str, parsing->width, parsing->len, '0');
	else if (parsing->width > parsing->len && parsing->flag_minus == 1
		&& parsing->precision <= 0)
		res = ft_left(str, parsing->width, parsing->len, ' ');
	else if ((parsing->width >= parsing->len || parsing->width < parsing->len)
		&& parsing->flag_zero == 1 && parsing->precision > 0)
		res = ft_right(str, parsing->width, 0, '0');
	else if ((parsing->width >= parsing->len || parsing->width < parsing->len)
		&& parsing->precision > 0)
		res = ft_left(str, parsing->width, 0, ' ');
	else
		res = ft_strdup(str);
	parsing->len = ft_strlen(res);
	free(str);
	return (res);
}

static void		processing_unicode_2(t_parsing *parsing)
{
	if (parsing->letter == 'S' || (parsing->size == 2 &&
								parsing->letter == 's'))
		parsing->len = write(1, "(null)", 6);
	else
	{
		parsing->len = write(1, "\0", 1);
		return ;
	}
}

void			processing_unicode(t_parsing *parsing, va_list ap)
{
	wchar_t		*uni_str;
	wchar_t		uni_char;
	char		*str;

	uni_char = 0;
	uni_str = 0;
	if (parsing->letter == 'S' || (parsing->size == 2 &&
									parsing->letter == 's'))
		uni_str = va_arg(ap, wchar_t*);
	else if (parsing->letter == 'C' || (parsing->size == 2 &&
									parsing->letter == 'c'))
		uni_char = va_arg(ap, wchar_t);
	if (uni_char != 0 || uni_str != 0)
	{
		str = ft_make_str_unicode(parsing, uni_str, uni_char);
		str = ft_width_unicode(parsing, str);
		ft_putstr(str);
		parsing->len = ft_strlen(str);
		free(str);
	}
	else
	{
		processing_unicode_2(parsing);
	}
}
