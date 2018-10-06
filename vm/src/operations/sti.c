/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:55 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/07 00:46:15 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline int		set_val_neg(t_car *self, t_vm *v, long arg_sum)
{
	const unsigned int	res = self->reg[self->arg_val[0]];
	const unsigned int	size = sizeof(res);
	const unsigned int	memsz = (ft_abs(arg_sum) > PC_IND) ? MEM_SIZE : 0;
	int					i;
	int					module;

	module = arg_sum + PC_IND;
	i = -1;
	while (++i < size)
		print_arena(v->arena + (memsz + module + i) % MEM_SIZE,
		PUMPKIN, self, v);
	return (module);
}

static inline int		set_val(t_car *self, t_vm *v, long arg_sum)
{
	const unsigned int	res = self->reg[self->arg_val[0]];
	const unsigned int	size = sizeof(res);
	unsigned char		*arena;
	int					i;
	int					module;

	arena = v->arena;
	module = PC_IND + arg_sum % IDX_MOD;
	i = -1;
	while (++i < size)
		print_arena(arena + (module + i) % MEM_SIZE, PUMPKIN, self, v);
	return (module);
}

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
		- SHORT_RANGE) > MEM_SIZE  && args[0] > FPOS1) || ((args[0] % SHORT_RANGE) == (args[0]
		% MEM_SIZE)) || ((args[0] % SHORT_RANGE - SHORT_RANGE) % IDX_MOD == args[0] % IDX_MOD - IDX_MOD 
		&& ft_abs(args[0] - SHORT_RANGE) > MEM_SIZE) || (ft_abs(args[0] % SHORT_RANGE - SHORT_RANGE) <= MEM_SIZE)
		|| (args[0] % MEM_SIZE == args[0] % SHORT_RANGE && args[0] > SHORT_RANGE + MEM_SIZE)
		|| (((args[0] % MEM_SIZE) - (args[0] % IDX_MOD)) == IDX_MOD)))
			args[0] = args[0] % IDX_MOD - IDX_MOD;
	}
	args[1] = self->args[2] == T_REG ?
	self->reg[self->arg_val[2]] : self->arg_val[2];
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
		- SHORT_RANGE) > MEM_SIZE && args[1] > FPOS1) || ((args[1] % SHORT_RANGE) == (args[1]
		% MEM_SIZE)) || ((args[0] % SHORT_RANGE - SHORT_RANGE) % IDX_MOD == args[0] % IDX_MOD - IDX_MOD 
		&& ft_abs(args[0] - SHORT_RANGE) > MEM_SIZE) || (ft_abs(args[1] % SHORT_RANGE - SHORT_RANGE) <= MEM_SIZE) // or ft_abs <= IDX_MOD?
		|| (args[1] % MEM_SIZE == args[1] % SHORT_RANGE && args[1] > SHORT_RANGE + MEM_SIZE)
		|| (((args[1] % MEM_SIZE) - (args[1] % IDX_MOD)) == IDX_MOD)))
			args[1] = args[1] % IDX_MOD - IDX_MOD;
	}
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
	if (A.verbose_value & 4 && I.cur_cycle != 2719)
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

	args[0] = 0;
	args[1] = 0;
	if (I.cur_cycle == 11914)
		ft_printf("");
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
