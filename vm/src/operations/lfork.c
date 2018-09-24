/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:51:41 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/23 20:00:52 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		lfork(t_car *self, t_vm *v)
{
	const int		space_to_end = MEM_SIZE - PC_IND;
	unsigned char	*pc;
	t_car			tmp;
	int				argv_nil;

	if (self->id == 27)
		ft_printf("");
	if ((self->arg_val[0] > MEM_SIZE && self->arg_val[0] % IDX_MOD == self->arg_val[0] % MEM_SIZE)
	|| (self->arg_val[0] <= MEM_SIZE))
		argv_nil = self->arg_val[0];
	else if (self->arg_val[0] > MEM_SIZE)
		argv_nil = self->arg_val[0] % MEM_SIZE;
	// argv_nil = (self->arg_val[0] > MEM_SIZE) ? self->arg_val[0] % MEM_SIZE : self->arg_val[0];
	pc = (argv_nil > space_to_end) ?
	v->arena + (argv_nil - space_to_end) % MEM_SIZE
	: self->pc + argv_nil;
	if (argv_nil > space_to_end && self->arg_val[0] % IDX_MOD != self->arg_val[0] % MEM_SIZE)
		argv_nil -= MEM_SIZE;
	if (A.verbose_value & 4)
		self->arg_val[0] > MEM_SIZE ? ft_printf("P %4d | lfork %d (%d)\n", self->id, argv_nil, PC_IND + argv_nil)
		: ft_printf("P %4d | lfork %d (%d)\n", self->id, self->arg_val[0], PC_IND + self->arg_val[0]);
	copy_car(self, v, pc);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
