/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:55 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/22 20:49:17 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		sti(t_car *self, t_vm *v)
{
	unsigned char	*pc;
	int				arg_sum;

	if (self->args[1] == T_IND)
	{
		self->arg_val[1] %= IDX_MOD;
		if (self->arg_val[1] > MEM_SIZE - (self->pc - v->arena))
			pc = &v->arena[self->arg_val[1] - MEM_SIZE - (self->pc - v->arena)];
		else
			pc = &self->pc[self->arg_val[1]];
		arg_sum = get_raw_num(pc, 4) + self->arg_val[2];
	}
	else
		arg_sum = self->arg_val[1] + self->arg_val[2];
	arg_sum %= IDX_MOD;
	if (arg_sum > MEM_SIZE - (self->pc - v->arena))
		pc = &v->arena[arg_sum - MEM_SIZE - (self->pc - v->arena)];
	else
		pc = &self->pc[arg_sum];
	*pc = self->arg_val[0];
	move_pc(self, v, self->pc_padding);
	self->pc_padding = 0;
}
