/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:47:36 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/14 20:00:42 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		ld(t_car *self, t_vm *v)
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
		self->arg_val[0] %= IDX_MOD;
		ft_printf("ft_uns_strlen(self->pc): %d", ft_strlen((char*)self->pc));
		if (self->arg_val[0] > ft_strlen((char*)self->pc))
			pc = &self->pc[self->arg_val[0] - ft_strlen((char*)self->pc)];
		else
			pc = &self->pc[self->arg_val[0]];
		self->reg[self->arg_val[i]] = get_raw_num(pc, 4);
		self->carry = self->reg[self->arg_val[i]] ? 0 : 1;
	}
	ft_printf("%0.2x %0.2x %0.2x\n", self->arg_val[0], self->arg_val[1], self->arg_val[2]);
	ft_printf("%0.2u %0.2u %d\n", self->arg_val[i], self->reg[self->arg_val[i]], self->carry);
}
