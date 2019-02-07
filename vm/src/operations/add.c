/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:48:13 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/07 14:47:01 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

inline static void	verbose_add(int car_id, int r1, int r2, int r3)
{
	ft_printf("P %4d | add r%d r%d r%d\n", car_id, r1, r2, r3);
}

void				add(t_car *self, t_vm *v)
{
	int		val1;
	int		val2;

	val1 = self->reg[self->arg_val[0]];
	val2 = self->reg[self->arg_val[1]];
	self->reg[self->arg_val[2]] = val1 + val2;
	self->carry = self->reg[self->arg_val[2]] ? false : true;
	if (IS_VERB(4))
		verbose_add(self->id, self->arg_val[0],
		self->arg_val[1], self->arg_val[2]);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
