/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:48:50 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/15 03:56:19 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		and(t_car *self, t_vm *v)
{
	unsigned int		first_arg;
	unsigned int		second_arg;

	first_arg = (self->args[0] == T_REG) ? self->reg[self->arg_val[0]] : self->arg_val[0];
	second_arg = (self->args[1] == T_REG) ? self->reg[self->arg_val[1]] : self->arg_val[1];
	self->reg[self->arg_val[2]] = first_arg & second_arg;
	self->carry = self->reg[self->arg_val[2]] ? false : true;
	if (A.verbose_value & 4)
		ft_printf("P %4d | and %d %d r%d\n", self->id, first_arg, second_arg, self->arg_val[2]);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}