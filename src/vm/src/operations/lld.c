/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:50:31 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/23 18:33:31 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		lld(t_car *self, t_vm *v)
{
	int				i;
	unsigned char	*pc;

	i = 0;
	while (self->args[i] != T_REG)
		i++;
	if (i > 2)
		return ;
	if (self->args[0] == T_DIR)
		self->reg[self->arg_val[i]] = self->arg_val[0];
	else if (self->args[0] == T_IND)
	{
		if (self->arg_val[0] > MEM_SIZE - (self->pc - v->arena))
			pc = &v->arena[self->arg_val[0] - MEM_SIZE - (self->pc - v->arena)];
		else
			pc = &self->pc[self->arg_val[0]];
		self->reg[self->arg_val[i]] = get_raw_num(pc, 4);
	}
	self->carry = self->reg[self->arg_val[i]] ? false : true;
	move_pc(self, v, self->pc_padding);
	self->pc_padding = 0;
}
