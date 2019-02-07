/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:48:50 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/07 14:25:15 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

inline static void	verbose_and(int car_id, int v1, int v2, int reg)
{
	ft_printf("P %4d | and %d %d r%d\n", car_id, v1, v2, reg);
}

void				and(t_car *self, t_vm *v)
{
	int		f_arg;
	int		s_arg;

	f_arg = obtain_argval(v, self, 0, true);
	s_arg = obtain_argval(v, self, 1, true);
	self->reg[self->arg_val[2]] = f_arg & s_arg;
	self->carry = self->reg[self->arg_val[2]] ? false : true;
	if (IS_VERB(4))
		verbose_and(self->id, f_arg, s_arg, self->arg_val[2]);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
