/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:50:31 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/16 15:21:02 by vbrazas          ###   ########.fr       */
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
		if (self->arg_val[0] > ft_strlen((char*)self->pc))
			pc = &v->arena[self->arg_val[0] - ft_strlen((char*)self->pc)];
		else
			pc = &self->pc[self->arg_val[0]];
		self->reg[self->arg_val[i]] = get_raw_num(pc, 4);
		self->carry = self->reg[self->arg_val[i]] ? false : true;
	}
}
