/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:55 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/02 20:19:22 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static void		set_value(t_car *self, t_vm *v, int arg_sum)
{
	int				ind;
	size_t			size;
	unsigned int	res;
	
	res = self->reg[self->arg_val[0]];
	size = sizeof(res);
	ft_printf("size: %d\n", size);
	ind = -1;
	if (MOD(arg_sum) > self->pc - v->arena)
	{
		while (++ind < size)
		{
			v->arena[MEM_SIZE + arg_sum - (self->pc - v->arena) + ind] = 0;
			v->arena[MEM_SIZE + arg_sum - (self->pc - v->arena) + ind] |= (res << (8 * ind)) >> (8 * (size - 1));
			ft_printf("%u ; %0.2x\t||\t", self->reg[self->arg_val[0]],v->arena[MEM_SIZE + arg_sum - (self->pc - v->arena) + ind]);
		}
	}
	else
	{
		while (++ind < size)
		{
			v->arena[self->pc - v->arena + arg_sum + ind] = 0;
			v->arena[self->pc - v->arena + arg_sum + ind] |= (res << (8 * ind)) >> (8 * (size - 1));
			ft_printf("%u ; %0.2x\t||\t", self->reg[self->arg_val[0]], v->arena[self->pc - v->arena + arg_sum + ind]);
		}
	}
}

static void		set_val(t_car *self, t_vm *v, int arg_sum)
{
	int				ind;
	int				size;
	unsigned int	res;

	res = self->reg[self->arg_val[0]];
	size = sizeof(res);
	ft_printf("size: %d\n", size);
	ind = -1;
	if (arg_sum > MEM_SIZE - (self->pc - v->arena))
	{
		while (++ind < size)
		{
			v->arena[arg_sum - (MEM_SIZE - (self->pc - v->arena)) + ind] = 0;
			v->arena[arg_sum - (MEM_SIZE - (self->pc - v->arena)) + ind] |= (res << (8 * ind)) >> (8 * (size - 1));   //??????????????????????????
			ft_printf("%u ; %0.2x\t||\t", self->reg[self->arg_val[0]], v->arena[arg_sum - (MEM_SIZE - (self->pc - v->arena)) + ind]);
		}
	}
	else
	{
		while (++ind < size)
		{
			self->pc[arg_sum + ind] = 0;
			self->pc[arg_sum + ind] |= (res << (8 * ind)) >> (8 * (size - 1));
			ft_printf("%u ; %0.2x\t||\t", self->reg[self->arg_val[0]], self->pc[arg_sum + ind]);
		}
	}
}

void			sti(t_car *self, t_vm *v)
{
	unsigned char	*pc;
	int				arg_sum;

	if (self->args[1] == T_IND)
	{
		self->arg_val[1] %= IDX_MOD;
		if (self->arg_val[1] > MEM_SIZE - (self->pc - v->arena))
			pc = &v->arena[self->arg_val[1] - MEM_SIZE - (self->pc - v->arena)];
		else
			pc = &self->pc[self->arg_val[1]];
		arg_sum = get_raw_num(pc, 4) + self->arg_val[2];
	}
	else
		arg_sum = self->arg_val[1] + self->arg_val[2];
	if (arg_sum > IDX_MOD)
	{
		arg_sum %= IDX_MOD;	
		arg_sum -= IDX_MOD;
		set_value(self, v, arg_sum);
	}
	else
	{
		if (arg_sum == IDX_MOD)
			arg_sum %= IDX_MOD;
		set_val(self, v, arg_sum);
	}
	
	// int i = arg_sum;
	// ft_printf("STI_pc reg_value is: %0.2x\n", self->reg[self->arg_val[0]]);
	// ft_printf("STI_pc is: ");
	// while (i < arg_sum + 10)
	// 	ft_printf("%0.2x ", self->pc[i++]);
	ft_putchar('\n');
	move_pc(self, v, self->pc_padding);
	self->pc_padding = 0;
}
