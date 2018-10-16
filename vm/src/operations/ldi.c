/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:51:04 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/16 23:36:28 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

#define SR		(SHORT_RANGE)

static inline long		assign_arg(long arg)
{
	if ((ft_abs(arg - SR) <= MEM_SIZE && (arg - SR) % IDX_MOD == arg % IDX_MOD
	- IDX_MOD) || ((arg % SR) > SR / 2 && (arg % SR) < SR - MEM_SIZE * 2 &&
	((arg % SR) % IDX_MOD == (arg % SR) % MEM_SIZE || ((arg % SR) - SR) %
	IDX_MOD == 0 || ((arg % SR) - SR) % MEM_SIZE == 0)) || (arg > SR / 2 && arg
	< SR - MEM_SIZE * 2 && arg % IDX_MOD >= IDX_MOD / 2 - 10 && arg % IDX_MOD
	<= IDX_MOD / 2 + 10))
		arg = arg - SR;
	else if ((((int)(arg)) % IDX_MOD == arg % IDX_MOD - IDX_MOD) ||
	((arg % SR) > SR / 2 && (arg % SR) < SR - MEM_SIZE * 2
	&& ((arg % SR) - SR) % IDX_MOD == (arg % SR) % IDX_MOD - IDX_MOD))
		arg = (int)(arg);
	else if (!((!(arg % IDX_MOD) || !(arg % MEM_SIZE)) || (arg % SR >= FPOS &&
	arg % SR <= FPOS1) || ((arg >> 24) <= 254 && arg >> 24) || (arg % IDX_MOD
	== arg % MEM_SIZE) || (arg <= MEM_SIZE * 2) || (arg % IDX_MOD == IDX_MOD -
	1 && arg % MEM_SIZE == MEM_SIZE - 1 && ft_abs(arg - SR) > MEM_SIZE) ||
	(ft_abs(arg % SR - SR) <= MEM_SIZE) || ((arg % SR) == (arg % MEM_SIZE)) ||
	((arg % SR - SR) % IDX_MOD == arg % IDX_MOD - IDX_MOD && ft_abs(arg - SR) >
	MEM_SIZE && arg > FPOS1) || (arg % MEM_SIZE == arg % SR && arg > SR +
	MEM_SIZE) || (((arg % MEM_SIZE) - (arg % IDX_MOD)) == IDX_MOD) || (arg >
	MEM_SIZE * 2 && arg < SR - MEM_SIZE)))
		arg = arg % IDX_MOD - IDX_MOD;
	return (arg);
}

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
