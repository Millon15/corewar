/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:51:04 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/20 22:28:13 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void			ldi(t_car *self, t_vm *v)
{
	unsigned char	*pc;
	unsigned int	arg_sum;

	if (self->args[0] == T_IND)
	{
		self->arg_val[0] %= IDX_MOD;
		if (self->arg_val[0] > MEM_SIZE - (self->pc - v->arena))
			pc = &v->arena[self->arg_val[0] - MEM_SIZE - (self->pc - v->arena)];
		else
			pc = &self->pc[self->arg_val[0]];
		arg_sum = get_raw_num(pc, 4) + self->arg_val[1];
	}
	else
		arg_sum = self->arg_val[0] + self->arg_val[1];
	arg_sum %= IDX_MOD;
	if (arg_sum > MEM_SIZE - (self->pc - v->arena))
		pc = &v->arena[arg_sum - MEM_SIZE - (self->pc - v->arena)];
	else
		pc = &self->pc[arg_sum];
	self->reg[self->arg_val[2]] = get_raw_num(pc, 4);
	self->pc = MOVE_PC(v->arena, self->pc, self->pc_padding);
	self->pc_padding = 0;
}
