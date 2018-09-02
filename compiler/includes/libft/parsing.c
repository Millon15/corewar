/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:05:04 by ndidenko          #+#    #+#             */
/*   Updated: 2018/05/02 16:05:05 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_parse_flags(char *conv, t_parsing *parsing)
{
	int count;

	count = 0;
	conv += 1;
	while (ft_valid_flag(*conv))
	{
		if (*conv == '#')
			parsing->flag_sharp = 1;
		if (*conv == '0')
			parsing->flag_zero = 1;
		if (*conv == '-')
			parsing->flag_minus = 1;
		if (*conv == '+')
			parsing->flag_plus = 1;
		if (*conv == ' ')
			parsing->flag_space = 1;
		conv++;
		count++;
	}
	while (*conv)
		conv++;
	parsing->letter = *(conv - 1);
	return (count);
}

int		ft_parse_width(char *conv, t_parsing *parsing)
{
	int		count;
	char	*ptr;
	char	*width;

	count = 0;
	conv += 1;
	while (ft_valid_flag(*conv))
		conv++;
	if (ft_is_digit(*conv) == 0)
		return (0);
	ptr = conv;
	while (ft_is_digit(*conv))
	{
		count++;
		conv++;
	}
	width = ft_strsub(ptr, 0, count);
	parsing->width = ft_atoi(width);
	free(width);
	return (count);
}

void	ft_detect_precision(char *conv, t_parsing *parsing)
{
	while (*conv)
	{
		if (*conv == '.')
			parsing->precision = 0;
		conv++;
	}
}

int		ft_parse_precision(char *conv, t_parsing *parsing)
{
	int		count;
	char	*ptr;
	char	*ptr2;
	char	*precision;

	count = 0;
	ptr = 0;
	while (*conv)
	{
		if (*conv == '.' && ft_is_digit(*(conv + 1)))
			ptr = conv + 1;
		conv++;
	}
	if (ptr != 0)
	{
		ptr2 = ptr;
		while (ft_is_digit(*ptr++))
			count++;
		precision = ft_strsub(ptr2, 0, count);
		parsing->precision = ft_atoi(precision);
		free(precision);
	}
	return (0);
}

int		ft_parse_size(char *conv, t_parsing *parsing)
{
	while (ft_valid_modifier(*conv) == 0)
		conv++;
	while (ft_valid_modifier(*conv) == 1)
	{
		if (*conv == 'h' && *(conv + 1) == 'h' && parsing->size < 0)
		{
			parsing->size = 0;
			conv += 2;
		}
		if (*conv == 'h' && *(conv + 1) != 'h' && parsing->size < 1)
			parsing->size = 1;
		if (*conv == 'l' && *(conv + 1) != 'l' && parsing->size < 2)
		{
			parsing->size = 2;
			conv += 2;
		}
		if (*conv == 'l' && *(conv + 1) == 'l' && parsing->size < 3)
			parsing->size = 3;
		if (*conv == 'j' && parsing->size < 4)
			parsing->size = 4;
		if (*conv == 'z')
			parsing->size = 5;
		conv++;
	}
	return (0);
}
