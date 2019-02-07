/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:51:41 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/07 14:52:29 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

inline static void	verbose_lfork(t_car *self, int val)
{
	ft_printf("P %4d | lfork %d (%d)\n", self->id, val, self->pc_ind + val);
}

void				lfork(t_car *self, t_vm *v)
{
	int	f_arg;

	f_arg = obtain_argval(v, self, 0, true);
	copy_car(self, v, find_addr(PC_IND + f_arg));
	self->pc_ind = PC_IND;
	if (IS_VERB(4))
		verbose_lfork(self, f_arg);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
