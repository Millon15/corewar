/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_conv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:03:57 by ndidenko          #+#    #+#             */
/*   Updated: 2018/05/02 16:03:58 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_print_conv(char *conv, va_list ap)
{
	t_parsing parsing;

	ft_struct_init(&parsing);
	ft_parse_flags(conv, &parsing);
	ft_parse_width(conv, &parsing);
	ft_detect_precision(conv, &parsing);
	if (parsing.precision == 0)
		ft_parse_precision(conv, &parsing);
	ft_parse_size(conv, &parsing);
	processing_letter(&parsing, ap);
	return (parsing.len);
}

void	processing_letter(t_parsing *parsing, va_list ap)
{
	if (parsing->letter == 'c' && parsing->size != 2)
		processing_c(parsing, ap);
	else if (parsing->letter == 's' && parsing->size != 2)
		processing_s(parsing, ap);
	else if (parsing->letter == 'd' || parsing->letter == 'D' ||
		parsing->letter == 'i')
		processing_d(parsing, ap);
	else if (parsing->letter == 'u' || parsing->letter == 'U')
		processing_u(parsing, ap);
	else if (parsing->letter == 'o' || parsing->letter == 'O')
		processing_o(parsing, ap);
	else if (parsing->letter == 'x' || parsing->letter == 'X')
		processing_x(parsing, ap);
	else if (parsing->letter == 'p')
		processing_p(parsing, ap);
	else if (parsing->letter == 'S' || parsing->letter == 'C')
		processing_unicode(parsing, ap);
	else if (parsing->size == 2
		&& (parsing->letter == 'c' || parsing->letter == 's'))
		processing_unicode(parsing, ap);
	else if (parsing->letter == '%')
		processing_pct(parsing);
	else
		processing_invalid(parsing);
}
