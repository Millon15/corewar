/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:45 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/18 16:28:58 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		lldi(t_car *self, t_vm *v)
{
	unsigned char	*pc;
	int				arg_sum;

	if (self->args[0] == T_IND)
	{
		self->arg_val[0] %= IDX_MOD;
		if (self->arg_val[0] > MEM_SIZE - (self->pc - v->arena))
			pc = &v->arena[self->arg_val[0] - MEM_SIZE - (self->pc - v->arena)];
		else
			pc = &self->pc[self->arg_val[0]];
		arg_sum = get_raw_num(pc, 4) + self->arg_val[1];
		arg_sum %= IDX_MOD;
	}
	else
		arg_sum = self->arg_val[0] + self->arg_val[1];
	if (arg_sum > MEM_SIZE - (self->pc - v->arena))
		pc = &v->arena[arg_sum - MEM_SIZE - (self->pc - v->arena)];
	else
		pc = &self->pc[arg_sum];
	self->arg_val[2] = get_raw_num(pc, 4);
	self->carry = self->arg_val[2] ? false : true;
	self->pc = MOVE_PC(v->arena, self->pc, self->pc_padding);
	self->pc_padding = 0;
}
