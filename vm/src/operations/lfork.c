/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:51:41 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/19 20:34:42 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		lfork(t_car *self, t_vm *v)
{
	const int		to_subtract = MEM_SIZE - PC_IND;
	unsigned char	*pc;
	t_car			tmp;
	int				argv_nil;

	argv_nil = (self->arg_val[0] > MEM_SIZE) ? self->arg_val[0] % MEM_SIZE : self->arg_val[0];
	pc = (argv_nil > to_subtract) ?
	v->arena + (argv_nil - to_subtract) % MEM_SIZE
	: self->pc + argv_nil;
	if (argv_nil > to_subtract)
		argv_nil -= MEM_SIZE;
	if (A.verbose_value & 4)
		ft_printf("P %4d | lfork %d (%d)\n", self->id, argv_nil, PC_IND + argv_nil);
	copy_car(self, v, pc);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
