/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:51:04 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/14 23:36:58 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void			ldi(t_car *self, t_vm *v)
{
	unsigned char	*pc;
	int				arg_sum;
	unsigned int	first_arg;
	unsigned int	sec_arg;
	int				fa;
	int				sa;

	if (self->args[0] == T_IND)
	{
		self->arg_val[0] %= IDX_MOD;
		if (self->arg_val[0] > MEM_SIZE - PC_IND)
			pc = &v->arena[self->arg_val[0] - MEM_SIZE - PC_IND];
		else
			pc = &self->pc[self->arg_val[0]];
		first_arg = get_raw_num(pc, REG_SIZE, v);
	}
	else
		first_arg = (self->args[0] == T_REG) ? self->reg[self->arg_val[0]] : self->arg_val[0];
	if (first_arg >= IDX_MOD)
	{
		first_arg %= IDX_MOD;
		// if (first_arg != IDX_MOD)		
		fa = first_arg - IDX_MOD;
	}
	else
		fa = first_arg;
	sec_arg = (self->args[1] == T_REG) ? self->reg[self->arg_val[1]] : self->arg_val[1];
	if (sec_arg >= IDX_MOD)
	{
		sec_arg %= IDX_MOD;
		// if (sec_arg != IDX_MOD)		
		sa = sec_arg - IDX_MOD;
	}
	else
		sa = sec_arg;
	arg_sum = fa + sa;
	arg_sum += PC_IND;
	// arg_sum %= IDX_MOD;
	if (arg_sum < 0)
		pc = &v->arena[MEM_SIZE - mod(arg_sum) % MEM_SIZE];
	else
		pc = &v->arena[arg_sum % MEM_SIZE];
	// if (arg_sum > MEM_SIZE - PC_IND)
	// 	pc = &v->arena[arg_sum - MEM_SIZE - PC_IND];
	// else
	// 	pc = &self->pc[arg_sum];
	self->reg[self->arg_val[2]] = get_raw_num(pc, REG_SIZE, v);
	if (A.verbose_value & 4)
	{
		ft_printf("P %4d | ldi %d %d r%d\n", self->id, fa, sa, self->arg_val[2]);
		ft_printf("%8c -> load from %d + %d = %d (with pc and mod %d)\n", '|',
		fa, sa, fa + sa, arg_sum);
	}
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
