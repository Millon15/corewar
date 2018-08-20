/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:51:41 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/20 22:28:08 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		lfork(t_car *self, t_vm *v)
{
	unsigned char	*pc;
	t_car			tmp;

	if (self->arg_val[0] > MEM_SIZE - (self->pc - v->arena))
		pc = &v->arena[self->arg_val[0] - MEM_SIZE - (self->pc - v->arena)];
	else
		pc = &self->pc[self->arg_val[0]];
	copy_car_to_end(self, v, pc);
	self->pc = MOVE_PC(v->arena, self->pc, self->pc_padding);
	self->pc_padding = 0;
}
