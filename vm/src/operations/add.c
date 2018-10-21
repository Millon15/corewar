/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:48:13 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/20 21:34:12 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		add(t_car *self, t_vm *v)
{
	int		val1;
	int		val2;

	val1 = self->reg[self->arg_val[0]];
	val2 = self->reg[self->arg_val[1]];
	self->reg[self->arg_val[2]] = val1 + val2;
	self->carry = self->reg[self->arg_val[2]] ? false : true;
	if (IS_VERB(4))
		ft_printf("P %4d | add r%d r%d r%d\n"
		, self->id, self->arg_val[0], self->arg_val[1], self->arg_val[2]);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
