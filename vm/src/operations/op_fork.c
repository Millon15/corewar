/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:50:06 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/29 21:40:33 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		op_fork(t_car *self, t_vm *v)
{
	const int		space_to_end = MEM_SIZE - PC_IND;
	unsigned char	*pc;
	t_car			tmp;
	int				arg;

	if (self->id == 45 && I.cur_cycle > 4800)
		ft_printf("");
	arg = self->arg_val[0] % IDX_MOD;
	if (self->arg_val[0] >= IDX_MOD)
	{
		// if (arg >= IDX_MOD / 2)
		if (self->arg_val[0] > MEM_SIZE && arg && self->arg_val[0] % arg) // or self->arg_val[0] % IDX_MOD, (which is arg) == self->arg_val[0] % MEM_SIZE
			arg -= IDX_MOD;
		pc = (mod(arg) > PC_IND) ? 
		v->arena + (MEM_SIZE + arg + PC_IND) % MEM_SIZE
		: v->arena + (PC_IND + arg) % MEM_SIZE;
	}
	else
		pc = (arg > space_to_end) ?
		v->arena + (arg - space_to_end) % MEM_SIZE
		: self->pc + arg;
	if (A.verbose_value & 4)
		arg > 0 ? ft_printf("P %4d | fork %d (%d)\n", self->id, self->arg_val[0], (pc - v->arena) % MEM_SIZE)
		: ft_printf("P %4d | fork %d (%d)\n", self->id, !((self->arg_val[0] % MEM_SIZE) % IDX_MOD) && self->arg_val[0]
		? -IDX_MOD : pc - self->pc, (pc - v->arena) % MEM_SIZE);
	copy_car(self, v, pc);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
