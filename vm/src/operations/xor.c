/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:23 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/20 21:34:56 by vbrazas          ###   ########.fr       */
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
	else
	{
		pc = v->arena + (PC_IND + self->arg_val[i] % IDX_MOD) % MEM_SIZE;
		arg = get_raw_num(pc, 4, v);
	}
	return (arg);
}

void				xor(t_car *self, t_vm *v)
{
	unsigned int				first_arg;
	unsigned int				second_arg;

	first_arg = calc_arg(self, v, 0);
	second_arg = calc_arg(self, v, 1);
	self->reg[self->arg_val[2]] = first_arg ^ second_arg;
	self->carry = self->reg[self->arg_val[2]] ? false : true;
	if (IS_VERB(4))
		ft_printf("P %4d | xor %d %d r%d\n"
		, self->id, first_arg, second_arg, self->arg_val[2]);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
