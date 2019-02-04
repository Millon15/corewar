/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:50:31 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/04 21:52:15 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void				lld(t_car *self, t_vm *v)
{
	int		f_arg;

	f_arg = obtain_argval(v, self, 0, false);
	self->reg[self->arg_val[1]] = f_arg;
	self->carry = self->reg[self->arg_val[1]] ? false : true;
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
