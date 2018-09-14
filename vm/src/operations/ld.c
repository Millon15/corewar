/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:47:36 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/14 23:36:58 by vbrazas          ###   ########.fr       */
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
		if (self->arg_val[0] > MEM_SIZE - PC_IND)
			pc = &v->arena[self->arg_val[0] - MEM_SIZE - PC_IND];
		else
			pc = &self->pc[self->arg_val[0]];
		self->reg[self->arg_val[1]] = get_raw_num(pc, REG_SIZE, v);
	}
	self->carry = self->reg[self->arg_val[1]] ? false : true;
	if (A.verbose_value & 4)
		ft_printf("P %4d | ld %d r%d\n", self->id,  self->reg[self->arg_val[1]], self->arg_val[1]);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
