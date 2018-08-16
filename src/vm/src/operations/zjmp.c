/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:34 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/16 15:22:10 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		zjmp(t_car *self, t_vm *v)
{
	if (self->carry == false)
		return ;
	self->arg_val[0] %= IDX_MOD;
	if (self->arg_val[0] > ft_strlen((char*)self->pc))
		self->pc = &v->arena[self->arg_val[0] - ft_strlen((char*)self->pc)];
	else
		self->pc += self->arg_val[0];
}
