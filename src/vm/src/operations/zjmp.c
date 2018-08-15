/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:34 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/15 21:50:23 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void zjmp(t_car *self, t_vm *v)
{
	if (self->carry == 1)
	{
		self->arg_val[0] %= IDX_MOD;
		if (self->arg_val[0] > ft_strlen((char*)self->pc))
			self->pc = &self->ar_start[self->arg_val[0] - ft_strlen((char*)self->pc)];
		else
			self->pc += self->arg_val[0];
	}
}
