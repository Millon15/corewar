/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2to10.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 18:57:28 by ndidenko          #+#    #+#             */
/*   Updated: 2018/05/02 18:57:30 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_2to10(char *bin)
{
	int step;
	int sum;
	int bit;

	if (!bin)
		return (0);
	step = 0;
	sum = 0;
	bit = 1;
	while (*bin++)
		step++;
	bin -= 2;
	while (step != 0)
	{
		if (*bin == '1')
			sum += bit;
		bit *= 2;
		bin--;
		step--;
	}
	return (sum);
}
