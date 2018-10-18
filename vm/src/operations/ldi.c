/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:51:04 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/18 19:41:18 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		set_args(long *args, t_car *self)
{
	if (args[0] >= IDX_MOD)
		args[0] = assign_arg(args[0]);
	args[1] = self->args[1] == T_REG ?
	self->reg[self->arg_val[1]] : self->arg_val[1];
	if (args[1] >= IDX_MOD)
		args[1] = assign_arg(args[1]);
}

static inline void		load_va_v(t_car *self, t_vm *v, long *args)
{
	long				arg_sum;
	unsigned char		*pc;

	arg_sum = ((int)(args[0] + args[1])) % IDX_MOD + PC_IND;
	if (arg_sum < 0)
		pc = &v->arena[MEM_SIZE - ft_abs(arg_sum) % MEM_SIZE];
	else
		pc = &v->arena[arg_sum % MEM_SIZE];
	self->reg[self->arg_val[2]] = get_raw_num(pc, REG_SIZE, v);
	if (A.verbose_value & 4)
	{
		ft_printf("P %4d | ldi %d %d r%d\n", self->id, args[0],
		args[1], self->arg_val[2]);
		ft_printf("%8c -> load from %d + %d = %d (with pc and mod %d)\n", '|',
		args[0], args[1], args[0] + args[1], arg_sum);
	}
}

void					ldi(t_car *self, t_vm *v)
{
	unsigned char		*pc;
	long				args[2];

	ft_bzero((void *)args, sizeof(long) * 2);
	if (self->args[0] == T_IND)
	{
		self->arg_val[0] %= IDX_MOD;
		if (self->arg_val[0] > MEM_SIZE - PC_IND)
			pc = &v->arena[self->arg_val[0] - MEM_SIZE - PC_IND];
		else
			pc = &self->pc[self->arg_val[0]];
		args[0] = get_raw_num(pc, REG_SIZE, v);
	}
	else
		args[0] = (self->args[0] == T_REG)
		? self->reg[self->arg_val[0]] : self->arg_val[0];
	set_args(args, self);
	load_va_v(self, v, args);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
