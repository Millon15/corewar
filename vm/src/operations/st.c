/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:40:59 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/07 15:05:28 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

inline static void	verbose_st(int car_id, int reg, int val)
{
	ft_printf("P %4d | st r%d %d\n", car_id, reg, val);
}

void				st(t_car *self, t_vm *v)
{
	int				pc;
	int				i;
	const int		res = self->reg[self->arg_val[0]];

	i = -1;
	pc = self->arg_val[1];
	if (self->args[1] == T_REG)
		self->reg[pc] = res;
	else
		while (++i < 4)
			print_arena(v->arena + find_addr(PC_IND + pc % IDX_MOD + i),
			TO_ARENA, self, v);
	if (IS_VERB(4))
		verbose_st(self->id, self->arg_val[0], pc);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
