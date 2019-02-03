/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:40:36 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/03 22:31:25 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

#define IND(x)		(x - 1)

// inline int8_t	get_byte(t_vm *vm, int32_t pc, int32_t step)
// {
// 	return (vm->arena[calc_addr(pc + step)]);
// }

int			get_op_arg(t_vm *v, t_car *self, int index, bool mod)
{
	int			value;
	int			addr;

	value = 0;
	if (self->args[index] & T_REG || self->args[index] & T_DIR)
		value = self->arg_val[index];
	else if (self->args[index] & T_IND)
	{
		addr = self->arg_val[index];
		value = get_raw_num(&v->arena[PC_IND + (mod ? (addr % IDX_MOD) : addr) % MEM_SIZE] ,REG_SIZE, v);
	}
	return (value);
}

void				ld(t_car *self, t_vm *v)
{
	self->reg[self->arg_val[1]] = get_op_arg(v, self, 0, true);
	self->carry = self->reg[self->arg_val[1]] ? false : true;
	if (IS_VERB(4))
		ft_printf("P %4d | ld %d r%d\n", self->id,
		self->reg[self->arg_val[1]], self->arg_val[1]);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
