/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:47:59 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/30 08:27:28 by akupriia         ###   ########.fr       */
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
	int					tmp;

	i = -1;
	if (self->id == 45 && I.cur_cycle > 4200)
		ft_printf("");
	// first_arg = res % IDX_MOD;
	tmp = self->arg_val[1];
	if (self->args[1] == T_IND)
	{
		if (tmp > IDX_MOD && !(tmp % IDX_MOD))
			first_arg = 0;
		else if ((tmp > SHORT_RANGE / 2) && (tmp % IDX_MOD == tmp % MEM_SIZE)
		&& (tmp - SHORT_RANGE) % IDX_MOD == tmp % IDX_MOD - IDX_MOD)
			first_arg = tmp - SHORT_RANGE;
		else if ((tmp >= FPOS && tmp <= FPOS1))
			first_arg = tmp;
		else if ((tmp > IDX_MOD && tmp > MEM_SIZE && tmp <= MEM_SIZE * 2)
		|| (tmp % IDX_MOD == tmp % MEM_SIZE))
		{
			// if (res > IDX_MOD && res % first_arg == 0) //or tmp % fa == 0??
			first_arg = tmp;
		}
		else if (tmp == FPOS || tmp == FPOS1)
			first_arg = tmp;
		else if (tmp > MEM_SIZE && tmp < FPOS && (tmp - SHORT_RANGE) % IDX_MOD == tmp % IDX_MOD - IDX_MOD)
			first_arg = tmp;
		else
		// if (tmp % IDX_MOD != 0)
		{
			first_arg = (tmp > IDX_MOD) ?
			tmp % IDX_MOD : tmp;
			if (tmp > MEM_SIZE)
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
		if (tmp > SHORT_RANGE / 2 && tmp <= SHORT_RANGE
		&& tmp % IDX_MOD == IDX_MOD / 2)
			first_arg = tmp - SHORT_RANGE;
		else if (tmp > IDX_MOD && tmp <= MEM_SIZE && !(tmp % IDX_MOD))
			first_arg = tmp;
		else if (tmp > MEM_SIZE && !(tmp % IDX_MOD)
		&& !(tmp % MEM_SIZE))
			first_arg = tmp - SHORT_RANGE;
		else if (tmp > MEM_SIZE && !(tmp % IDX_MOD)
		&& (tmp % MEM_SIZE) <= MEM_SIZE / 2 && !((tmp % MEM_SIZE) % IDX_MOD))
			first_arg = tmp;
		else if (tmp > MEM_SIZE && !(tmp % IDX_MOD))
			first_arg -= IDX_MOD;
	}
	else if (self->args[1] == T_REG)
		self->reg[tmp] = res;
	if (A.verbose_value & 4)
		ft_printf("P %4d | st r%d %d\n", self->id, self->arg_val[0],
		(tmp <= MEM_SIZE) ? tmp : first_arg);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
