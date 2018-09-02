/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 17:14:27 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/21 17:14:29 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v'
			|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

int			ft_atoi(const char *str)
{
	size_t				i;
	unsigned long long	nbr;
	int					negative;

	nbr = 0;
	negative = 1;
	i = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-')
		negative = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && (str[i] >= '0') && (str[i] <= '9'))
	{
		nbr = (nbr * 10) + ((unsigned long long)str[i] - '0');
		i++;
	}
	if ((nbr > 9223372036854775807 || i > 19) && negative == 1)
		return (-1);
	if ((nbr > 9223372036854775807 || i > 19) && negative == -1)
		return (0);
	else
		return ((int)nbr * negative);
}
