/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:45 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/07 15:05:24 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

inline static void	verbose_lldi(t_car *self, int v1, int v2, int reg)
{
	ft_printf("P %4d | ldi %d %d r%d\n", self->id, v1, v2, reg);
	ft_printf("%8c -> load from %d + %d = %d (with pc and mod %d)\n", '|', v1,
	v2, v1 + v2, self->pc_ind + (v1 + v2));
}

void				lldi(t_car *self, t_vm *v)
{
	int		f_arg;
	int		s_arg;

	f_arg = obtain_argval(v, self, 0, true);
	s_arg = obtain_argval(v, self, 1, true);
	self->reg[self->arg_val[2]] = get_raw_num(&v->arena[find_addr(PC_IND +
	f_arg + s_arg)], REG_SIZE, v);
	self->pc_ind = PC_IND;
	if (IS_VERB(4))
		verbose_lldi(self, f_arg, s_arg, self->arg_val[2]);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
