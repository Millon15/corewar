/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   botsize.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 19:30:18 by ndidenko          #+#    #+#             */
/*   Updated: 2018/09/02 19:30:21 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				ft_botsize(t_champ *main_struct)
{
	int			res;
	t_arg		*arg;
	t_command	*command;

	res = 0;
	command = main_struct->cmds;
	while (command)
	{
		if (!ft_strequ(command->name, "-1"))
		{
			res = res + 1;
			if (command->codage)
				res = res + 1;
			arg = command->inst;
			while (arg)
			{
				res = res + arg->size;
				arg = arg->next;
			}
		}
		command = command->next;
	}
	return (res);
}
