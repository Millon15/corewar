/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:51:41 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/14 23:36:58 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		lfork(t_car *self, t_vm *v)
{
	const int		to_subtract = MEM_SIZE - PC_IND;
	unsigned char	*pc;
	t_car			tmp;

	pc = (self->arg_val[0] > to_subtract) ?
	v->arena + (self->arg_val[0] - to_subtract) % MEM_SIZE
	: self->pc + self->arg_val[0];
	if (A.verbose_value & 4)
		ft_printf("P %4d | lfork %d (%d)\n", self->id, self->arg_val[0], PC_IND + self->arg_val[0]);
	copy_car(self, v, pc);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
