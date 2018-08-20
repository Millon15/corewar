/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:47:59 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/20 22:30:24 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		st(t_car *self, t_vm *v)
{
	unsigned char	*pc;
	int				ind;
	
	ind = -1;
	if (self->args[1] == T_IND)
	{
		self->arg_val[1] %= IDX_MOD;
		if (self->arg_val[1] > MEM_SIZE - (self->pc - v->arena))
			while (++ind < 4)
			{
				v->arena[self->arg_val[1] - MEM_SIZE - (self->pc - v->arena) + ind] = (self->reg[self->arg_val[0]] << ind * 2) >> 6;
				v->color[self->arg_val[1] - MEM_SIZE - (self->pc - v->arena) + ind] = v->player[UINT_MAX - self->whom].color;
			}		
		else
			while (++ind < 4)
			{
				self->pc[self->arg_val[1] + ind] = (self->reg[self->arg_val[0]] << ind * 2) >> 6;
				v->color[self->pc - v->arena + self->arg_val[1] + ind] = v->player[UINT_MAX - self->whom].color;
			}
	}
	else if (self->args[1] == T_REG)
		self->reg[self->arg_val[1]] = self->reg[self->arg_val[0]];
	self->pc = MOVE_PC(v->arena, self->pc, self->pc_padding);
	self->pc_padding = 0;
}
