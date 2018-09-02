/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 15:57:44 by ndidenko          #+#    #+#             */
/*   Updated: 2018/05/02 15:57:46 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_search_conversion_letter(char *str)
{
	size_t	i;
	char	*letter;
	int		x;

	x = 0;
	i = 1;
	letter = "cCsSpdDioOuUxX%rRZAaBbEeFfGgHIJKkLMmNnQqTtVvWwYy";
	while (str[i])
	{
		if (x == 48)
		{
			x = 0;
			i++;
		}
		if (str[i] != letter[x])
			x++;
		else if (str[i] == letter[x])
			return (i + 1);
	}
	return (0);
}

static void		ft_myprint2(char **str, int *len, va_list ap)
{
	char	*conv;
	size_t	result_letter;

	result_letter = ft_search_conversion_letter(*str);
	if (result_letter == 0)
	{
		ft_putstr(*str);
		*len += ft_strlen(*str);
		*str += ft_strlen(*str);
		return ;
	}
	conv = ft_strsub(*str, 0, result_letter);
	if (ft_validconv(conv) == -1)
	{
		*str += (result_letter);
		*len += ft_print_conv(conv, ap);
	}
	else
		*str += ft_validconv(conv);
	ft_strdel(&conv);
}

int				ft_myprint(char *str, va_list ap)
{
	int len;

	len = 0;
	while (*str)
	{
		if (*str == '%' && (ft_validchar(str + 1) == 0 || *(str + 1) == '\0'))
			str += 1;
		else if (*str != '%')
		{
			ft_putchar(*str++);
			len += 1;
		}
		else if (*str == '%')
		{
			ft_myprint2(&str, &len, ap);
		}
	}
	return (len);
}

void			ft_struct_init(t_parsing *parsing)
{
	parsing->flag_sharp = 0;
	parsing->flag_zero = 0;
	parsing->flag_minus = 0;
	parsing->flag_plus = 0;
	parsing->flag_space = 0;
	parsing->width = -1;
	parsing->precision = -1;
	parsing->size = -1;
	parsing->letter = 0;
	parsing->len = 0;
}

int				ft_printf(char *str, ...)
{
	int			len;
	va_list		ap;

	va_start(ap, str);
	len = ft_myprint(str, ap);
	va_end(ap);
	return (len);
}
