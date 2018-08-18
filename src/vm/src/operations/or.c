/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:13 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/18 16:29:00 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		or(t_car *self, t_vm *v)
{
	self->arg_val[2] = self->args[0] | self->args[1];
	self->carry = self->arg_val[2] ? false : true;
	self->pc = MOVE_PC(v->arena, self->pc, self->pc_padding);
	self->pc_padding = 0;
}
