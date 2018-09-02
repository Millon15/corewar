/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:49:20 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/30 16:07:10 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(int nbr)
{
	int len;
	int nbr_buff;

	if (nbr == 0)
		return (1);
	len = 0;
	nbr_buff = nbr;
	while (nbr_buff)
	{
		nbr_buff = nbr_buff / 10;
		len++;
	}
	if (nbr < 0)
		return (len + 1);
	else
		return (len);
}

char		*ft_itoa(int n)
{
	int		nbr;
	int		len;
	char	*str_new;

	len = ft_nbrlen(n);
	nbr = n;
	str_new = ft_strnew(len);
	if (str_new == 0)
		return (0);
	while (len--)
	{
		if (n < 0)
			str_new[len] = (n % 10) * -1 + 48;
		else
			str_new[len] = (n % 10) + 48;
		n = n / 10;
	}
	if (nbr < 0)
		str_new[0] = '-';
	return (str_new);
}
