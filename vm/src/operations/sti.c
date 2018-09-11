/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:55 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/12 01:52:17 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#define PUMPKIN			(res << (8 * i)) >> (8 * (size - 1))

static inline int		set_val_neg(t_car *self, t_vm *v, int arg_sum)
{
	const unsigned int	res = self->reg[self->arg_val[0]];
	const unsigned int	size = sizeof(res);
	const unsigned int	memsz = (mod(arg_sum) > PC_DELTA) ? MEM_SIZE : 0;
	int					i;
	int					module;

	module = arg_sum + PC_DELTA;
	i = -1;
	while (++i < size)
		print_arena(v->arena + (memsz + module + i) % MEM_SIZE, PUMPKIN, self, v);
		// v->arena[(memsz + module + i) % MEM_SIZE] = PUMPKIN;
	return (module);
}

static inline int		set_val(t_car *self, t_vm *v, int arg_sum)
{
	const unsigned int	res = self->reg[self->arg_val[0]];
	const unsigned int	size = sizeof(res);
	unsigned char		*arena;
	int					i;
	int					module;

	arena = v->arena;
	if (arg_sum > MEM_SIZE - PC_DELTA)
		module = arg_sum - (MEM_SIZE - PC_DELTA);
	else
		module = arg_sum + PC_DELTA;
	i = -1;
	while (++i < size)
		print_arena(arena + (module + i) % MEM_SIZE, PUMPKIN, self, v);
		// arena[(module + i) % MEM_SIZE] = (res << (8 * i)) >> (8 * (size - 1));
	return (module);
}

void					sti(t_car *self, t_vm *v)
{
	unsigned char	*pc;
	int				arg_sum;
	unsigned int	first_arg;
	int				fa;
	int				module;
	unsigned int	sec_arg;
	int				sa;

	if (self->id == 23)
		ft_printf("");
	if (self->args[1] == T_IND)
	{
		self->arg_val[1] %= IDX_MOD;
		if (self->arg_val[1] > MEM_SIZE - PC_DELTA)
			pc = &v->arena[self->arg_val[1] - MEM_SIZE - PC_DELTA];
		else
			pc = &self->pc[self->arg_val[1]];
		first_arg = get_raw_num(pc, REG_SIZE, v);
	}
	else
		first_arg = self->args[1] == T_REG ? self->reg[self->arg_val[1]] : self->arg_val[1];
	if (first_arg >= IDX_MOD)
	{
		first_arg %= IDX_MOD;
		// if (first_arg != IDX_MOD)		
		fa = first_arg - IDX_MOD;
	}
	else
		fa = first_arg;
	sec_arg = self->args[2] == T_REG ? self->reg[self->arg_val[2]] : self->arg_val[2];
	if (sec_arg >= IDX_MOD)
	{
		sec_arg %= IDX_MOD;
		// if (sec_arg != IDX_MOD)		
		sa = sec_arg - IDX_MOD;
	}
	else
		sa = sec_arg;
	arg_sum = fa + sa;
	module = (arg_sum < 0) ? set_val_neg(self, v, arg_sum)
	: set_val(self, v, arg_sum);
	if (!module && !arg_sum)
		module = PC_DELTA;
	if (v->args.verbose_value & 4)
	{
		ft_printf("P %4d | sti r%d %d %d\n", self->id, self->arg_val[0], fa, sa);
		ft_printf("%8c -> store to %d + %d = %d (with pc and mod %d)\n", '|', fa, sa, arg_sum, module);
	}
	// int i = arg_sum;
	// ft_printf("STI_pc reg_value is: %0.2x\n", self->reg[self->arg_val[0]]);
	// ft_printf("STI_pc is: ");
	// while (i < arg_sum + 10)
		// ft_printf("%0.2x ", self->pc[i++]);
	// ft_putchar('\n');
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
