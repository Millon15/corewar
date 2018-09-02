/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 16:46:11 by ndidenko          #+#    #+#             */
/*   Updated: 2018/09/02 16:46:12 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_number_byte(t_command *start)
{
	int			count_bytes;
	t_arg		*arg;

	count_bytes = 0;
	while (start)
	{
		start->number_byte = count_bytes;
		arg = start->inst;
		while (arg)
		{
			count_bytes = count_bytes + arg->size;
			arg = arg->next;
		}
		count_bytes = count_bytes + (start->codage + 1);
		start = start->next;
	}
}

int			ft_set_codage(t_command *start)
{
	t_arg	*arg;
	int		codage;
	int		count;

	count = 3;
	arg = (start)->inst;
	codage = 0;
	while (count--)
	{
		if (arg)
		{
			codage = codage + arg->binary;
			arg = arg->next;
		}
		codage <<= 2;
	}
	return (codage);
}

static int	ft_findlabel(t_champ *a, char *name, int nbr)
{
	t_command	*start;
	t_label		*lbl;
	int			value;

	start = a->cmds;
	value = -1;
	while (start && value == -1)
	{
		lbl = start->labels;
		while (lbl && value == -1)
		{
			if (ft_strcmp(lbl->name, name) == 0)
				value = start->number_byte;
			lbl = lbl->next;
		}
		start = start->next;
	}
	if (value == -1)
		exit(ft_printf("ERROR! label not exist: |%s|\n", name));
	if (nbr > value)
		value = -1 * (nbr - value);
	else
		value = value - nbr;
	return (value);
}

void		ft_set_value2(t_champ *main_struct)
{
	t_command	*start;
	t_arg		*arg;

	start = (main_struct)->cmds;
	while (start)
	{
		arg = start->inst;
		while (arg)
		{
			if (arg->name_label && (int)arg->value == -1)
				arg->value = ft_findlabel(main_struct, arg->name_label,
												start->number_byte);
			arg = arg->next;
		}
		start = start->next;
	}
}

void		ft_set_value(t_champ **main_struct)
{
	t_command	*start;
	t_arg		*arg;

	ft_number_byte((*main_struct)->cmds);
	start = (*main_struct)->cmds;
	while (start)
	{
		arg = start->inst;
		if (start->codage)
			start->codage = ft_set_codage(start);
		start = start->next;
	}
	start = (*main_struct)->cmds;
	ft_set_value2(*main_struct);
}
