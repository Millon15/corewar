/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:34 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/22 21:15:47 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		zjmp(t_car *self, t_vm *v)
{
	int					num;
	const unsigned int	ui_max = -1;
	
	if (self->carry == false)
		return ;
	self->arg_val[0] %= IDX_MOD;
	if (self->arg_val[0] > &v->arena[((int)v->player[ui_max - WHOM(self)].prog_size)] - self->pc)
	move_pc(self, v, self->pc_padding);
	else
	{
		if (self->arg_val[0] > MEM_SIZE - (self->pc - v->arena))
			self->pc = &v->arena[self->arg_val[0] - MEM_SIZE - (self->pc - v->arena)];
		else
			self->pc += self->arg_val[0];
	}
	self->pc_padding = 0;
}
