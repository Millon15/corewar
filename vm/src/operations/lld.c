/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:50:31 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/07 14:52:43 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

inline static void	verbose_lld(int car_id, int val, int reg)
{
	ft_printf("P %4d | lld %d r%d\n", car_id, val, reg);
}

void				lld(t_car *self, t_vm *v)
{
	int		f_arg;

	f_arg = obtain_argval(v, self, 0, false);
	self->reg[self->arg_val[1]] = f_arg;
	self->carry = f_arg ? false : true;
	if (IS_VERB(4))
		verbose_lld(self->id, f_arg, self->arg_val[1]);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
