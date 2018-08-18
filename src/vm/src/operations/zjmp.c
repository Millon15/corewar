/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:34 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/18 16:26:37 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		zjmp(t_car *self, t_vm *v)
{
	int num;
	if (self->carry == false)
		return ;
	self->arg_val[0] %= IDX_MOD;
	if (self->arg_val[0] > MEM_SIZE - (self->pc - v->arena))
		self->pc = &v->arena[self->arg_val[0] - MEM_SIZE - (self->pc - v->arena)];
	else
		self->pc += self->arg_val[0];
	self->pc_padding = 0;
}
