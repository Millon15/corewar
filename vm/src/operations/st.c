/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:47:59 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/28 20:58:13 by akupriia         ###   ########.fr       */
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
	if (self->id == 35 && I.cur_cycle > 7100)
		ft_printf("");
	// first_arg = res % IDX_MOD;
	if (self->args[1] == T_IND)
	{
		if (self->arg_val[1] > IDX_MOD && !(self->arg_val[1] % IDX_MOD))
			first_arg = 0;
		else if ((self->arg_val[1] > IDX_MOD && self->arg_val[1] > MEM_SIZE && self->arg_val[1] <= MEM_SIZE * 2)
		|| (self->arg_val[1] % IDX_MOD == self->arg_val[1] % MEM_SIZE))
		{
			// if (res > IDX_MOD && res % first_arg == 0) //or self->arg_val[1] % fa == 0??
			first_arg = self->arg_val[1];
		}
		else if (self->arg_val[1] == FPOS)
			first_arg = self->arg_val[1];
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
		{
			if (first_arg >= 0 && first_arg > space_to_end)
				pc_index = PC_IND + first_arg % IDX_MOD;
			else if (first_arg < 0 && mod(first_arg) > PC_IND)
				pc_index = MEM_SIZE + first_arg + PC_IND;
			else
				pc_index = first_arg % MEM_SIZE + PC_IND;
		}
		// 	pc_index = (mod(first_arg) > space_to_end) ?
		// (first_arg - space_to_end) : first_arg % MEM_SIZE + PC_IND;
		while (++i < 4)
			print_arena(v->arena +(pc_index + i) % MEM_SIZE, PUMPKIN, self, v);
			// v->arena[(pc_index + ind) % MEM_SIZE] = PUMPKIN;
		if (self->arg_val[1] > IDX_MOD && self->arg_val[1] <= MEM_SIZE && !(self->arg_val[1] % IDX_MOD))
			first_arg = self->arg_val[1];
		else if (self->arg_val[1] > MEM_SIZE && !(self->arg_val[1] % IDX_MOD))
			first_arg -= IDX_MOD;
	}
	else if (self->args[1] == T_REG)
		self->reg[self->arg_val[1]] = res;
	if (A.verbose_value & 4)
		ft_printf("P %4d | st r%d %d\n", self->id, self->arg_val[0],
		(self->arg_val[1] <= MEM_SIZE) ? self->arg_val[1] : first_arg);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
