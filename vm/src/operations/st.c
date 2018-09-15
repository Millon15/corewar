/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:47:59 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/15 03:23:20 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		st(t_car *self, t_vm *v)
{
	unsigned char		*pc;
	int					ind;
	int					pc_index;
	int					first_arg;

	ind = -1;
	first_arg = self->reg[self->arg_val[0]] % IDX_MOD;
	if (self->args[1] == T_IND)
	{
		first_arg = (self->arg_val[1] > IDX_MOD) ? self->arg_val[1] % IDX_MOD - IDX_MOD :
		self->arg_val[1];
		pc_index = (first_arg > MEM_SIZE - PC_IND) ? (first_arg - MEM_SIZE - PC_IND) : first_arg + PC_IND;
		while (++ind < 4)
			v->arena[(pc_index + ind) % MEM_SIZE] = (self->reg[self->arg_val[0]] << ind * 2) >> 6;
	}
	else if (self->args[1] == T_REG)
		self->reg[self->arg_val[1]] = self->reg[self->arg_val[0]];
	if (A.verbose_value & 4)
		ft_printf("P %4d | st r%d %d\n", self->id, self->arg_val[0], first_arg);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
