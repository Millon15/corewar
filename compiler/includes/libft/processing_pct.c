/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_pct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:06:57 by ndidenko          #+#    #+#             */
/*   Updated: 2018/05/02 16:06:58 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	processing_pct(t_parsing *parsing)
{
	char	*res;

	if (parsing->width > 0 && parsing->flag_minus == 1)
		res = ft_left("%", parsing->width, 1, ' ');
	else if (parsing->width > 0 && parsing->flag_zero == 1)
		res = ft_right("%", parsing->width, 1, '0');
	else if (parsing->width == -1)
		res = ft_left("%", 1, 1, '%');
	else
		res = ft_right("%", parsing->width, 1, ' ');
	ft_putstr(res);
	parsing->len += ft_strlen(res);
	free(res);
}
