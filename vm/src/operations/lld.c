/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:50:31 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/23 19:56:08 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		lld(t_car *self, t_vm *v)
{
	int				i;
	unsigned char	*pc;

	i = 0;
	if (self->args[0] == T_DIR)
		self->reg[self->arg_val[i]] = self->arg_val[0];
	else if (self->args[0] == T_IND)
	{
		if (self->arg_val[0] > MEM_SIZE - PC_IND)
			pc = &v->arena[self->arg_val[0] - MEM_SIZE - PC_IND];
		else
			pc = &self->pc[self->arg_val[0]];
		self->reg[self->arg_val[i]] = get_raw_num(pc, REG_SIZE, v);
	}
	self->carry = self->reg[self->arg_val[i]] ? false : true;
	if (A.verbose_value & 4)
		ft_printf("P %4d | lld %d r%d\n", self->id,  self->reg[self->arg_val[1]], self->arg_val[1]);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
