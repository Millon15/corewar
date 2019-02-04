/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:51:04 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/04 21:46:44 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void				ldi(t_car *self, t_vm *v)
{
	int		f_arg;
	int		s_arg;

	f_arg = obtain_argval(v, self, 0, true);
	s_arg = obtain_argval(v, self, 1, true);
	self->reg[self->arg_val[2]] = get_raw_num(&v->arena[(PC_IND + ((f_arg + s_arg) % IDX_MOD)) % MEM_SIZE],
				REG_SIZE, v);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}

