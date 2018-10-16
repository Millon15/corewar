/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:55 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/16 23:36:25 by akupriia         ###   ########.fr       */
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
	args[1] = self->args[2] == T_REG ?
	self->reg[self->arg_val[2]] : self->arg_val[2];
	if (args[1] >= IDX_MOD)
		args[1] = assign_arg(args[1]);
}

static inline void		set_va_v(long arg_sum, t_car *self, t_vm *v, long *args)
{
	int			module;

	if (arg_sum < 0)
		module = set_val_neg(self, v, arg_sum % IDX_MOD);
	else
		module = set_val(self, v, arg_sum);
	if (!module && !arg_sum)
		module = PC_IND;
	if (A.verbose_value & 4)
	{
		ft_printf("P %4d | sti r%d %d %d\n", self->id,
		self->arg_val[0], args[0], args[1]);
		if (module > MEM_SIZE)
			module = ((module - PC_IND) % IDX_MOD) + PC_IND;
		ft_printf("%8c -> store to %d + %d = %d (with pc and mod %d)\n", '|',
		args[0], args[1], arg_sum, module);
	}
}

void					sti(t_car *self, t_vm *v)
{
	unsigned char		*pc;
	int					arg_sum;
	long				args[2];

	ft_bzero((void *)args, sizeof(long) * 2);
	if (self->args[1] == T_IND)
	{
		self->arg_val[1] %= IDX_MOD;
		if (self->arg_val[1] >= SPACE_TO_END)
			pc = &v->arena[self->arg_val[1] - SPACE_TO_END];
		else
			pc = &self->pc[self->arg_val[1]];
		args[0] = get_raw_num(pc, REG_SIZE, v);
	}
	else
		args[0] = self->args[1] == T_REG ?
		self->reg[self->arg_val[1]] : self->arg_val[1];
	set_args(args, self);
	arg_sum = args[0] + args[1];
	set_va_v(arg_sum, self, v, args);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
