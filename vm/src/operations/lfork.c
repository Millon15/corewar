/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:51:41 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/04 23:22:21 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		lfork(t_car *self, t_vm *v)
{
	int	f_arg;

	f_arg = obtain_argval(v, self, 0, true);
	copy_car(self, v, &v->arena[(PC_IND + f_arg) % MEM_SIZE]);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
