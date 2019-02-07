/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:13 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/07 14:32:22 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

inline static void	verbose_or(int car_id, int v1, int v2, int reg)
{
	ft_printf("P %4d | or %d %d r%d\n", car_id, v1, v2, reg);
}

void				or(t_car *self, t_vm *v)
{
	int		f_arg;
	int		s_arg;

	f_arg = obtain_argval(v, self, 0, true);
	s_arg = obtain_argval(v, self, 1, true);
	self->reg[self->arg_val[2]] = f_arg | s_arg;
	self->carry = self->reg[self->arg_val[2]] ? false : true;
	if (IS_VERB(4))
		verbose_or(self->id, f_arg, s_arg, self->arg_val[2]);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
