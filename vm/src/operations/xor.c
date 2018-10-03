/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:23 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/03 09:17:44 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static unsigned int	calc_arg(t_car *self, t_vm *v, int i)
{
	unsigned int		arg;
	const unsigned char	*pc;

	if (self->args[i] == T_REG)
		arg = self->reg[self->arg_val[i]];
	else if (self->args[i] == T_DIR)
	{
		arg = self->arg_val[i];
		if (*(self->pc + 1) >= 240)
			arg -= SHORT_RANGE;
	}
	else if (self->args[i] == T_IND)
	{
		// arg = (int)self->arg_val[i];

		pc = v->arena + (PC_IND + self->arg_val[i] % IDX_MOD) % MEM_SIZE;
		arg = get_raw_num(pc, 4, v);
		// read_arena(core, (champions->pc - get_size_param(instruction->type)
		// 		+ (instruction->params[param - 1]
		// 		% IDX_MOD)) % MEM_SIZE, 4);
		// if (*(self->pc + 1) >= 240)
		// 	arg -= SHORT_RANGE;
		// arg %= IDX_MOD;
		// }
	}
	return (arg);
}

void		xor(t_car *self, t_vm *v)
{
	unsigned int				first_arg;
	unsigned int				second_arg;

	if (self->id == 2325 && I.cur_cycle == 14934)
		ft_printf("");
	if (self->id == 6)
		ft_printf("");
	// self->carry = false;
	// if (self->arg_val[0] % 16 == self->arg_val[0] % IDX_MOD)
	// 	first_arg = self->reg[self->arg_val[0] % IDX_MOD];
	// else
	// 	first_arg = (self->args[0] == T_REG) ?
	// 	self->reg[self->arg_val[0]] : self->arg_val[0];
	// if (self->arg_val[1] % 16 == self->arg_val[1] % IDX_MOD)
	// 	second_arg = self->reg[self->arg_val[1] % IDX_MOD];
	// else
	// 	second_arg = (self->args[1] == T_REG) ?
	// 	self->reg[self->arg_val[1]] : self->arg_val[1];
	first_arg = calc_arg(self, v, 0);
	second_arg = calc_arg(self, v, 1);
	self->reg[self->arg_val[2]] = first_arg ^ second_arg;
	self->carry = self->reg[self->arg_val[2]] ? false : true;
	if (A.verbose_value & 4)
		ft_printf("P %4d | xor %d %d r%d\n"
		, self->id, first_arg, second_arg, self->arg_val[2]);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}