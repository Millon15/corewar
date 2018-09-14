/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:50:06 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/14 05:44:13 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		op_fork(t_car *self, t_vm *v)
{
	const int		to_subtract = MEM_SIZE - PC_DELTA;
	unsigned char	*pc;
	t_car			tmp;
	int				arg;

	arg = self->arg_val[0] % IDX_MOD;
	if (self->arg_val[0] >= IDX_MOD)
	{
		if (arg >= IDX_MOD / 2)
			arg -= IDX_MOD;
		pc = (mod(arg) > PC_DELTA) ? 
		v->arena + (MEM_SIZE + arg + PC_DELTA)
		: v->arena + (PC_DELTA + arg);
	}
	else
		pc = (arg > to_subtract) ?
		v->arena + (arg - to_subtract)
		: self->pc + arg;
	if (A.verbose_value & 4)
		arg > 0 ? ft_printf("P %4d | fork %d (%d)\n", self->id, self->arg_val[0], pc - v->arena)
		: ft_printf("P %4d | fork %d (%d)\n", self->id, pc - self->pc, pc - v->arena);
	copy_car(self, v, pc);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
