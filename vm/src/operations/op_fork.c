/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:50:06 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/07 14:53:23 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

inline static void	verbose_fork(t_car *self, int val)
{
	ft_printf("P %4d | fork %d (%d)\n", self->id, val,
	self->pc_ind + val % IDX_MOD);
}

void				op_fork(t_car *self, t_vm *v)
{
	int		f_arg;
	int		position;

	f_arg = obtain_argval(v, self, 0, true);
	position = find_addr(PC_IND + f_arg % IDX_MOD);
	copy_car(self, v, position);
	self->pc_ind = PC_IND;
	if (IS_VERB(4))
		verbose_fork(self, f_arg);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
