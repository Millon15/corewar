/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 14:30:38 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/30 15:46:46 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *string)
{
	char	*strcopy;
	size_t	i;

	i = 0;
	strcopy = (char*)malloc(sizeof(char) * ft_strlen(string) + 1);
	if (strcopy == 0)
		return (0);
	while (string[i])
	{
		strcopy[i] = string[i];
		i++;
	}
	strcopy[i] = '\0';
	return (strcopy);
}
