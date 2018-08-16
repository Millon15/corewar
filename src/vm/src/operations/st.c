/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:47:59 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/16 15:20:52 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		st(t_car *self, t_vm *v)
{
	unsigned char	*pc;

	if (self->args[1] == T_IND)
	{
		self->arg_val[1] %= IDX_MOD;
		if (self->arg_val[1] > ft_strlen((char*)self->pc))
			pc = &v->arena[self->arg_val[0] - ft_strlen((char*)self->pc)];
		else
			pc = &self->pc[self->arg_val[1]];
		*pc = self->arg_val[0];
	}
	else if (self->args[1] == T_REG)
		self->reg[self->arg_val[1]] = self->arg_val[0];
}
