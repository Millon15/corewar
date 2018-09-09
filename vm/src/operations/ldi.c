/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:51:04 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/09 20:00:45 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void			ldi(t_car *self, t_vm *v)
{
	unsigned char	*pc;
	int				arg_sum;
	unsigned int	first_arg;

	if (self->args[0] == T_IND)
	{
		self->arg_val[0] %= IDX_MOD;
		if (self->arg_val[0] > MEM_SIZE - (PC_DELTA))
			pc = &v->arena[self->arg_val[0] - MEM_SIZE - (PC_DELTA)];
		else
			pc = &self->pc[self->arg_val[0]];
		first_arg = get_raw_num(pc, 4);
	}
	else
		first_arg = self->arg_val[0];
	if (first_arg >= IDX_MOD)
	{
		first_arg %= IDX_MOD;
		if (first_arg != IDX_MOD)		
			first_arg -= IDX_MOD;
	}
	if (self->arg_val[1] >= IDX_MOD)
	{
		self->arg_val[1] %= IDX_MOD;
		if (self->arg_val[1] != IDX_MOD)		
			self->arg_val[1] -= IDX_MOD;
	}
	arg_sum = first_arg + self->arg_val[1];
	arg_sum += PC_DELTA;
	// arg_sum %= IDX_MOD;
	if (arg_sum < 0)
		pc = &v->arena[MEM_SIZE - mod(arg_sum) % MEM_SIZE];
	else
		pc = &v->arena[arg_sum % MEM_SIZE];
	// if (arg_sum > MEM_SIZE - (PC_DELTA))
	// 	pc = &v->arena[arg_sum - MEM_SIZE - (PC_DELTA)];
	// else
	// 	pc = &self->pc[arg_sum];
	self->reg[self->arg_val[2]] = get_raw_num(pc, 4);
	if (v->args.verbose_value & 4)
	{
		ft_printf("P    %d | ldi %d %d r%d\n", self->id, first_arg, self->arg_val[1], self->arg_val[2]);
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
			first_arg, self->arg_val[1], first_arg + self->arg_val[1], arg_sum);
	}
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
