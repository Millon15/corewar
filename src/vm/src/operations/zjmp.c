/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:34 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/20 20:51:43 by akupriia         ###   ########.fr       */
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
	if (self->arg_val[0] > &v->arena[((int)v->player[ui_max - self->whom].prog_size)] - self->pc)
		self->pc = MOVE_PC(v->arena, self->pc, self->pc_padding);
	else
	{
		if (self->arg_val[0] > MEM_SIZE - (self->pc - v->arena))
			self->pc = &v->arena[self->arg_val[0] - MEM_SIZE - (self->pc - v->arena)];
		else
			self->pc += self->arg_val[0];
	}
	self->pc_padding = 0;
}
