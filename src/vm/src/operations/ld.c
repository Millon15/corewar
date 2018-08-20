/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:47:36 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/20 21:25:36 by akupriia         ###   ########.fr       */
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
	self->pc = MOVE_PC(v->arena, self->pc, self->pc_padding);
	self->pc_padding = 0;
}
