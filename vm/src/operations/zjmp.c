/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:34 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/04 22:22:24 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void			zjmp(t_car *self, t_vm *v)
{
	int			f_arg;

	f_arg = obtain_argval(v, self, 0, true);
	self->carry ? move_pc(self, v, f_arg % IDX_MOD, false) : move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
