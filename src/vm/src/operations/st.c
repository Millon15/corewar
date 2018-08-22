/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:47:59 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/22 20:49:14 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		st(t_car *self, t_vm *v)
{
	unsigned char	*pc;

	if (self->args[1] == T_IND)
	{
		self->arg_val[1] %= IDX_MOD;
		if (self->arg_val[1] > MEM_SIZE - (self->pc - v->arena))
			pc = &v->arena[self->arg_val[0] - MEM_SIZE - (self->pc - v->arena)];
		else
			pc = &self->pc[self->arg_val[1]];
		*pc = self->arg_val[0];
	}
	else if (self->args[1] == T_REG)
		self->reg[self->arg_val[1]] = self->arg_val[0];
	move_pc(self, v, self->pc_padding);
		self->pc_padding = 0;
}
