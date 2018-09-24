/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:48:13 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/23 20:00:39 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		add(t_car *self, t_vm *v)
{
	self->reg[self->arg_val[2]] = self->reg[self->arg_val[0]] + self->reg[self->arg_val[1]];
	self->carry = self->reg[self->arg_val[2]] ? false : true;
	if (A.verbose_value & 4)
		ft_printf("P %4d | add r%d r%d r%d\n", self->id, self->arg_val[0], self->arg_val[1], self->arg_val[2]);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
