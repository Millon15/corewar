/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:47:59 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/20 11:59:17 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		st(t_car *self, t_vm *v)
{
	unsigned char		*pc;
	int					i;
	int					pc_index;
	int					first_arg;
	const unsigned int	res = self->reg[self->arg_val[0]];
	const unsigned int	size = sizeof(res);
	const unsigned int	space_to_end = MEM_SIZE - PC_IND;

	i = -1;
	if (I.cur_cycle > 12000)
		ft_printf("");
	// first_arg = res % IDX_MOD;
	if (self->args[1] == T_IND)
	{
		if (self->arg_val[1] > IDX_MOD && self->arg_val[1] % IDX_MOD == 0)
		{
			// if (res > IDX_MOD && res % first_arg == 0) //or self->arg_val[1] % fa == 0??
				first_arg = self->arg_val[1];
		}
		else
		// if (self->arg_val[1] % IDX_MOD != 0)
		{
			first_arg = (self->arg_val[1] > IDX_MOD) ?
			self->arg_val[1] % IDX_MOD : self->arg_val[1];
			if (self->arg_val[1] > MEM_SIZE)
				first_arg -= IDX_MOD;
		}
		if (first_arg == IDX_MOD)
			pc_index = PC_IND;
		else
			pc_index = (mod(first_arg) > space_to_end) ?
		(first_arg - space_to_end) : first_arg % MEM_SIZE + PC_IND;
		while (++i < 4)
			print_arena(v->arena +(pc_index + i) % MEM_SIZE, PUMPKIN, self, v);
			// v->arena[(pc_index + ind) % MEM_SIZE] = PUMPKIN;
	}
	else if (self->args[1] == T_REG)
		self->reg[self->arg_val[1]] = res;
	if (A.verbose_value & 4)
		ft_printf("P %4d | st r%d %d\n", self->id, self->arg_val[0],
		(self->arg_val[1] <= MEM_SIZE) ? self->arg_val[1] : first_arg);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
