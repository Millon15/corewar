/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 17:02:10 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/18 17:34:37 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned char *unstr1;
	unsigned char *unstr2;

	unstr1 = (unsigned char*)str1;
	unstr2 = (unsigned char*)str2;
	while ((*unstr1 || *unstr2) && n)
	{
		if (*unstr1 != *unstr2)
			return (*unstr1 - *unstr2);
		unstr1++;
		unstr2++;
		n--;
	}
	return (0);
}
