/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:48:50 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/04 23:12:58 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void				and(t_car *self, t_vm *v)
{
	int		f_arg;
	int		s_arg;

	f_arg = obtain_argval(v, self, 0, true);
	s_arg = obtain_argval(v, self, 1, true);
	self->reg[self->arg_val[2]] = f_arg & s_arg;
	self->carry = self->reg[self->arg_val[2]] ? false : true;
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
