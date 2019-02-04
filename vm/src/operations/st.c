/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:40:59 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/04 22:09:53 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void					st(t_car *self, t_vm *v)
{
	int					pc;
	int					i;
	const int			res = self->reg[self->arg_val[0]];

	i = -1;
	pc = self->arg_val[1];
	if (self->args[1] == T_IND)
		self->reg[pc] = res;
	else
		while (++i < 4)
			print_arena(v->arena + (PC_IND + pc % IDX_MOD + i) % MEM_SIZE, TO_ARENA, self, v);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
