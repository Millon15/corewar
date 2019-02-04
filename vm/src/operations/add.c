/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:48:13 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/04 23:08:46 by akupriia         ###   ########.fr       */
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
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
