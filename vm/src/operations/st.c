/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:47:59 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/14 23:36:58 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		st(t_car *self, t_vm *v)
{
	unsigned char		*pc;
	int					ind;
	
	ind = -1;
	if (self->args[1] == T_IND)
	{
		self->arg_val[1] %= IDX_MOD;
		if (self->arg_val[1] > MEM_SIZE - PC_IND)
			while (++ind < 4)
				v->arena[self->arg_val[1] - MEM_SIZE - PC_IND + ind] = (self->reg[self->arg_val[0]] << ind * 2) >> 6;
		else
			while (++ind < 4)
				self->pc[self->arg_val[1] + ind] = (self->reg[self->arg_val[0]] << ind * 2) >> 6;
	}
	else if (self->args[1] == T_REG)
		self->reg[self->arg_val[1]] = self->arg_val[0];
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
