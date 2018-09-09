/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:55 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/09 19:43:38 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static int		set_value(t_car *self, t_vm *v, int arg_sum)
{
	int				ind;
	size_t			size;
	unsigned int	res;
	int				module;
	
	res = self->reg[self->arg_val[0]];
	size = sizeof(res);
	// ft_printf("size: %d\n", size);
	ind = -1;
	if (mod(arg_sum) > self->pc - v->arena)
	{
		// module = MEM_SIZE + arg_sum - (self->pc - v->arena);
		module = arg_sum + (self->pc - v->arena);
		while (++ind < size)
		{
			v->arena[module + ind] = 0;
			v->arena[module + ind] |= (res << (8 * ind)) >> (8 * (size - 1));
			// ft_printf("%u ; %0.2x\t||\t", self->reg[self->arg_val[0]],v->arena[MEM_SIZE + arg_sum - (self->pc - v->arena) + ind]);
		}
	}
	else
	{
		module = self->pc - v->arena + arg_sum;
		while (++ind < size)
		{
			v->arena[module + ind] = 0;
			v->arena[module + ind] |= (res << (8 * ind)) >> (8 * (size - 1));
			// ft_printf("%u ; %0.2x\t||\t", self->reg[self->arg_val[0]], v->arena[self->pc - v->arena + arg_sum + ind]);
		}
	}
	return (module);
}

static int		set_val(t_car *self, t_vm *v, int arg_sum)
{
	int				ind;
	int				size;
	unsigned int	res;
	int				module;

	res = self->reg[self->arg_val[0]];
	size = sizeof(res);
	// ft_printf("size: %d\n", size);
	ind = -1;
	if (arg_sum > MEM_SIZE - (self->pc - v->arena))
	{
		module = arg_sum - (MEM_SIZE - (self->pc - v->arena));
		while (++ind < size)
		{
			v->arena[module + ind] = 0;
			v->arena[module + ind] |= (res << (8 * ind)) >> (8 * (size - 1));   //??????????????????????????
			// ft_printf("%u ; %0.2x\t||\t", self->reg[self->arg_val[0]], v->arena[arg_sum - (MEM_SIZE - (self->pc - v->arena)) + ind]);
		}
	}
	else
	{
		module = arg_sum;
		while (++ind < size)
		{
			self->pc[module + ind] = 0;
			self->pc[module + ind] |= (res << (8 * ind)) >> (8 * (size - 1));
			// ft_printf("%u ; %0.2x\t||\t", self->reg[self->arg_val[0]], self->pc[arg_sum + ind]);
		}
	}
	return (module);
}

void			sti(t_car *self, t_vm *v)
{
	unsigned char	*pc;
	int				arg_sum;
	unsigned int	first_arg;
	int				fa;
	int				module;
	unsigned int	sec_arg;
	int				sa;

	if (self->args[1] == T_IND)
	{
		self->arg_val[1] %= IDX_MOD;
		if (self->arg_val[1] > MEM_SIZE - (self->pc - v->arena))
			pc = &v->arena[self->arg_val[1] - MEM_SIZE - (self->pc - v->arena)];
		else
			pc = &self->pc[self->arg_val[1]];
		first_arg = get_raw_num(pc, 4);	
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
	if (arg_sum < 0)
		module = set_value(self, v, arg_sum);
	else
		module = set_val(self, v, arg_sum);
	if (v->args.verbose_value & 4)
	{
		ft_printf("P    %d | sti r%d %d %d\n", self->id, self->arg_val[0], fa, sa);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n", fa, sa, arg_sum, module);
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
