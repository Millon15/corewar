/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:45 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/09 20:01:03 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		lldi(t_car *self, t_vm *v)
{
	unsigned char	*pc;
	unsigned int	arg_sum;

	if (self->args[0] == T_IND)
	{
		self->arg_val[0] %= IDX_MOD;
		if (self->arg_val[0] > MEM_SIZE - (PC_DELTA))
			pc = &v->arena[self->arg_val[0] - MEM_SIZE - (PC_DELTA)];
		else
			pc = &self->pc[self->arg_val[0]];
		arg_sum = get_raw_num(pc, 4) + self->arg_val[1];
		arg_sum %= IDX_MOD;
	}
	else
		arg_sum = self->arg_val[0] + self->arg_val[1];
	if (arg_sum > MEM_SIZE - (PC_DELTA))
		pc = &v->arena[arg_sum - MEM_SIZE - (PC_DELTA)];
	else
		pc = &self->pc[arg_sum];
	self->reg[self->arg_val[2]] = get_raw_num(pc, 4);
	self->carry = self->arg_val[2] ? false : true;
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
