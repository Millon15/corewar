/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:13 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/16 23:26:16 by akupriia         ###   ########.fr       */
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
		pc = v->arena + (PC_IND + self->arg_val[i] % IDX_MOD) % MEM_SIZE;
		arg = get_raw_num(pc, 4, v);
	}
	return (arg);
}

void				or(t_car *self, t_vm *v)
{
	unsigned int				first_arg;
	unsigned int				second_arg;

	first_arg = calc_arg(self, v, 0);
	second_arg = calc_arg(self, v, 1);
	self->reg[self->arg_val[2]] = first_arg | second_arg;
	self->carry = self->reg[self->arg_val[2]] ? false : true;
	if (A.verbose_value & 4)
		ft_printf("P %4d | or %d %d r%d\n"
		, self->id, first_arg, second_arg, self->arg_val[2]);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
