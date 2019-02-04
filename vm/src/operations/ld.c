/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:40:36 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/04 23:19:26 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void				ld(t_car *self, t_vm *v)
{
	self->reg[self->arg_val[1]] = obtain_argval(v, self, 0, true);
	self->carry = self->reg[self->arg_val[1]] ? false : true;
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
