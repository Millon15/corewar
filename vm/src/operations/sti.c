/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:55 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/07 15:05:33 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

inline static void	verbose_sti(t_car *self, int reg, int v1, int v2)
{
	ft_printf("P %4d | sti r%d %d %d\n", self->id, reg, v1, v2);
	ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n", v1,
		v2, v1 + v2, self->pc_ind + ((v1 + v2) % IDX_MOD));
}

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
		print_arena(v->arena + find_addr(PC_IND + (s_arg + t_arg)
		% IDX_MOD + i), TO_ARENA, self, v);
	self->pc_ind = PC_IND;
	if (IS_VERB(4))
		verbose_sti(self, self->arg_val[0], s_arg, t_arg);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
