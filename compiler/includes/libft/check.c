/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 15:57:18 by ndidenko          #+#    #+#             */
/*   Updated: 2018/05/02 15:57:19 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_validconv(char *conv)
{
	int count;

	count = 1;
	while (*conv++)
	{
		if (ft_strchr("cCsSpdDioOuUxX%hljz#-+ .0123456789", *conv) ||
				ft_strchr("rRZAaBbEeFfGgHIJKkLMmNnQqTtVvWwYy", *conv))
			count++;
		else
			return (count);
	}
	return (-1);
}

int	ft_validchar(char *str)
{
	if (ft_strchr("cCsSpdDioOuUxX%hljz#-+ .0123456789", *str) ||
			ft_strchr("rRZAaBbEeFfGgHIJKkLMmNnQqTtVvWwYy", *str))
		return (1);
	else
		return (0);
}

int	ft_valid_modifier(char c)
{
	return (ft_strchr("hljz", c) != 0);
}

int	ft_valid_flag(char c)
{
	return (ft_strchr("#0-+ ", c) != 0);
}

int	ft_is_digit(char c)
{
	return (ft_strchr("1234567890", c) != 0);
}
