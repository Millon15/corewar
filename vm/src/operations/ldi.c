/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:51:04 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/03 10:23:51 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		set_args(long *args, t_car *self)
{
	if (args[0] >= IDX_MOD)
	{
		if (((int)(args[0])) % IDX_MOD == args[0] % IDX_MOD - IDX_MOD)
			args[0] = (int)(args[0]);
		else if (ft_abs(args[0] - SHORT_RANGE) <= MEM_SIZE &&
		(args[0] - SHORT_RANGE) % IDX_MOD == args[0] % IDX_MOD - IDX_MOD)
			args[0] = args[0] - SHORT_RANGE;
		else if (!((!(args[0] % IDX_MOD) || !(args[0] %
		MEM_SIZE)) || (args[0] % SHORT_RANGE >= FPOS && args[0] % SHORT_RANGE <= FPOS1) || ((args[0] >>
		24) <= 254 && args[0] >> 24) || (args[0] % IDX_MOD == args[0] %
		MEM_SIZE) || (args[0] <= MEM_SIZE * 2) || (args[0] % IDX_MOD ==
		IDX_MOD - 1 && args[0] % MEM_SIZE == MEM_SIZE - 1 && ft_abs(args[0]
		- SHORT_RANGE) > MEM_SIZE) || ((args[0] % SHORT_RANGE) == (args[0]
		% MEM_SIZE)) || (args[0] % SHORT_RANGE - SHORT_RANGE == args[0]
		% IDX_MOD - IDX_MOD && ft_abs(args[0] - SHORT_RANGE) > MEM_SIZE) ||
		(args[0] % MEM_SIZE == args[0] % SHORT_RANGE && args[0] > SHORT_RANGE + MEM_SIZE)
		|| (((args[0] % MEM_SIZE) - (args[0] % IDX_MOD)) == IDX_MOD)))
			args[0] = args[0] % IDX_MOD - IDX_MOD;
	}
	args[1] = self->args[1] == T_REG ?
	self->reg[self->arg_val[1]] : self->arg_val[1];
	if (args[1] >= IDX_MOD)
	{
		if (((int)(args[1])) % IDX_MOD == args[1] % IDX_MOD - IDX_MOD)
			args[1] = (int)(args[1]);
		else if (ft_abs(args[1] - SHORT_RANGE) <= MEM_SIZE &&
		(args[1] - SHORT_RANGE) % IDX_MOD == args[1] % IDX_MOD - IDX_MOD)
			args[1] = args[1] - SHORT_RANGE;
		else if (!((!(args[1] % IDX_MOD) || !(args[1] %
		MEM_SIZE)) || (args[1] % SHORT_RANGE >= FPOS && args[1] % SHORT_RANGE <= FPOS1) || ((args[1] >>
		24) <= 254 && args[1] >> 24) || (args[1] % IDX_MOD == args[1] %
		MEM_SIZE) || (args[1] <= MEM_SIZE * 2) || (args[1] % IDX_MOD ==
		IDX_MOD - 1 && args[1] % MEM_SIZE == MEM_SIZE - 1 && ft_abs(args[1]
		- SHORT_RANGE) > MEM_SIZE) || ((args[1] % SHORT_RANGE) == (args[1]
		% MEM_SIZE)) || (args[1] % SHORT_RANGE - SHORT_RANGE == args[1]
		% IDX_MOD - IDX_MOD && ft_abs(args[1] - SHORT_RANGE) > MEM_SIZE) ||
		(args[1] % MEM_SIZE == args[1] % SHORT_RANGE && args[1] > SHORT_RANGE + MEM_SIZE)
		|| (((args[1] % MEM_SIZE) - (args[1] % IDX_MOD)) == IDX_MOD)))
			args[1] = args[1] % IDX_MOD - IDX_MOD;
	}
}

static inline void		load_va_v(t_car *self, t_vm *v, long *args)
{
	long				arg_sum;
	unsigned char		*pc;

	arg_sum = (args[0] + args[1]) % IDX_MOD + PC_IND;
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

	args[0] = 0;
	args[1] = 0;
	if (self->id == 8970 && I.cur_cycle == 10917)
		ft_printf("");
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
