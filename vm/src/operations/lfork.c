/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:51:41 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/09 22:40:09 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		lfork(t_car *self, t_vm *v)
{
	unsigned char	*pc;
	int				tmp;
	int				argv_nil;

	if (self->id == 107 && I.cur_cycle > 9242)
		ft_printf("");
	tmp = self->arg_val[0];
	if ((tmp > MEM_SIZE && tmp
	% IDX_MOD == tmp % MEM_SIZE)
	|| (tmp <= MEM_SIZE))
		argv_nil = tmp;
	else if (tmp > MEM_SIZE)
		argv_nil = tmp % MEM_SIZE;
	pc = (argv_nil >= SPACE_TO_END) ?
	v->arena + (argv_nil - SPACE_TO_END) % MEM_SIZE
	: self->pc + argv_nil;
	if (tmp > SHORT_RANGE / 2 && tmp < SHORT_RANGE - MEM_SIZE * 2)
		argv_nil = tmp - SHORT_RANGE;
	else if (argv_nil >= SPACE_TO_END && tmp %
	IDX_MOD != tmp % MEM_SIZE)
		argv_nil -= MEM_SIZE;
	if (A.verbose_value & 4)
		tmp > FPOS1 ? ft_printf("P %4d | lfork"
		" %d (%d)\n", self->id, argv_nil, PC_IND + argv_nil)
		: ft_printf("P %4d | lfork %d (%d)\n", self->id,
		tmp, PC_IND + tmp);
	copy_car(self, v, pc);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
