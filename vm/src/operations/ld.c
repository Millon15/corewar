/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:47:36 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/05 23:32:54 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		ld(t_car *self, t_vm *v)
{
	unsigned char	*pc;

	if (self->args[0] == T_DIR)
		self->reg[self->arg_val[1]] = self->arg_val[0];
	else if (self->args[0] == T_IND)
	{
		self->arg_val[0] %= IDX_MOD;
		if (self->arg_val[0] > MEM_SIZE - (self->pc - v->arena))
			pc = &v->arena[self->arg_val[0] - MEM_SIZE - (self->pc - v->arena)];
		else
			pc = &self->pc[self->arg_val[0]];
		self->reg[self->arg_val[1]] = get_raw_num(pc, 4);
	}
	self->carry = self->reg[self->arg_val[1]] ? false : true;
	if (v->args.verbose_value & 4)
		ft_printf("P\t%d | ld %d r%d\n", self->id,  self->reg[self->arg_val[1]], self->arg_val[1]);
	move_pc(self, v, self->pc_padding);
	self->pc_padding = 0;
}
