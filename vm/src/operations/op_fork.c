/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:50:06 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/11 01:24:56 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		op_fork(t_car *self, t_vm *v)
{
	const int		to_subtract = MEM_SIZE - PC_DELTA;
	unsigned char	*pc;
	t_car			tmp;
	int				arg;

	if (self->arg_val[0] >= IDX_MOD)
	{
		arg = self->arg_val[0] % IDX_MOD - IDX_MOD;
		pc = (mod(arg) > PC_DELTA) ? 
		v->arena + (MEM_SIZE + arg + PC_DELTA)
		: v->arena + (PC_DELTA + arg);
	}
	else
		pc = (self->arg_val[0] > to_subtract) ?
		v->arena + (self->arg_val[0] - to_subtract)
		: self->pc + self->arg_val[0];
	if (v->args.verbose_value & 4)
		ft_printf("P %4d | fork %d (%d)\n", self->id, pc - self->pc, pc - v->arena);
	copy_car(self, v, pc);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
