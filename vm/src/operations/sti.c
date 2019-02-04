/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:55 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/04 22:15:44 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void				sti(t_car *self, t_vm *v)
{
	int					s_arg;
	int					t_arg;
	int					i;
	const int			res = self->reg[self->arg_val[0]];

	i = -1;
	s_arg = obtain_argval(v, self, 1, true);
	t_arg = obtain_argval(v, self, 2, true);
	while (++i < 4)
		print_arena(v->arena + (PC_IND + (s_arg + t_arg) % IDX_MOD + i) % MEM_SIZE, TO_ARENA, self, v);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
