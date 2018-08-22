/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:23 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/22 20:49:22 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		xor(t_car *self, t_vm *v)
{
	self->arg_val[2] = self->args[0] ^ self->args[1];
	self->carry = self->arg_val[2] ? false : true;
	move_pc(self, v, self->pc_padding);
	self->pc_padding = 0;
}
