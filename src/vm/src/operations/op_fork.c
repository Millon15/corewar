/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:50:06 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/15 19:03:45 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void op_fork(t_car *self, t_vm *v)
{
	unsigned char	*pc;
	t_car			tmp;

	self->arg_val[0] %= IDX_MOD;
	if (self->arg_val[0] > ft_strlen((char*)self->pc))
		pc = &self->ar_start[self->arg_val[0] - ft_strlen((char*)self->pc)];
	else
		pc = &self->pc[self->arg_val[0]];
	tmp = *self;
	tmp.next = NULL;
	while (self)
		self = self->next;
	*self = tmp;
}
