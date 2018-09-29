/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:34 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/30 00:50:51 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		jump_car(t_car *self, t_vm *v, int val,
	bool is_jump_car)
{
	int					res;
	const unsigned int	space_to_end = MEM_SIZE - PC_IND;
	int					valmints;
	

	// 	if (MEM_SIZE - val > PC_IND)
	// 		res = -1 * (MEM_SIZE - val + PC_IND);
	// 	else
	// 		res = val;
		// res = (MEM_SIZE - val > PC_IND) ? (-1 * (MEM_SIZE - val + PC_IND)) : (val);
		// if (val - PC_IND > 0 && val - PC_IND > MEM_SIZE / 2)
		// 	res = -1 * (MEM_SIZE - val + PC_IND);
	res = (val - PC_IND > MEM_SIZE / 2) ?
	(-1 * (MEM_SIZE - val + PC_IND)) : (val);
	if (self->carry == true)
		move_pc(self, v, val, is_jump_car);
	if (self->arg_val[0] < FPOS || self->arg_val[0] % MEM_SIZE <= MEM_SIZE / 2)
		res = self->arg_val[0];	
	if (res + space_to_end == self->arg_val[0])
		res = self->arg_val[0];
	valmints = self->arg_val[0] - SHORT_RANGE;
	if (self->arg_val[0] > MEM_SIZE && self->arg_val[0] < SHORT_RANGE
	&& valmints % IDX_MOD == res)
		res = self->arg_val[0] - SHORT_RANGE;
	else if (self->arg_val[0] == FPOS)
		res = FPOS;
	else if (self->arg_val[0] == FPOS1)
		res = FPOS1;
	else if (self->arg_val[0] % IDX_MOD == self->arg_val[0] % MEM_SIZE)
		res = self->arg_val[0];
	if (A.verbose_value & 4)
		ft_printf("P %4d | zjmp %d %s\n", self->id, self->arg_val[0] <= MEM_SIZE * 2
		? self->arg_val[0] : res, (self->carry == true) ? "OK" : "FAILED");
}

// void					zjmp(t_car *self, t_vm *v)
// {
// 	unsigned int		space_to_end;
	
// 	if (self->arg_val[0] >= IDX_MOD)
// 	{
// 		self->arg_val[0] %= IDX_MOD;
// 		if (self->arg_val[0])
// 			self->arg_val[0] -= IDX_MOD;
// 		if (mod(self->arg_val[0]) > PC_IND)
// 			jump_car(self, v,
// 			MEM_SIZE - (mod(self->arg_val[0]) - PC_IND), true);
// 		else
// 			jump_car(self, v, self->arg_val[0], false);
// 	}
// 	else
// 	{
// 		space_to_end = MEM_SIZE - PC_IND;
// 		if (self->arg_val[0] > space_to_end)
// 			jump_car(self, v, self->arg_val[0] - space_to_end, true);
// 		else
// 			jump_car(self, v, self->arg_val[0], false);
// 	}
// 	if (self->carry == false)
// 		move_pc(self, v, self->pc_padding, false);
// 	self->pc_padding = 0;
// }

void					zjmp(t_car *self, t_vm *v)
{
	const unsigned int	space_to_end = MEM_SIZE - PC_IND;
	bool				fl;
	int					fa;

	if (I.cur_cycle > 4470 && self->id == 37)
		ft_printf("");
	// if (self->arg_val[0] >= IDX_MOD)
	if (self->arg_val[0] > FPOS && self->arg_val[0] % MEM_SIZE > MEM_SIZE / 2)
	{
		// fa = self->arg_val[0] % IDX_MOD;
		// if (self->arg_val[0] > MEM_SIZE)
			fa = self->arg_val[0] % IDX_MOD - IDX_MOD;
	}	
	else
		fa = self->arg_val[0];
	// if (self->arg_val[0] == FPOS)
	// {
	// 	fa = FPOS;
	// 	if (fa % IDX_MOD > space_to_end)
	// 		jump_car(self, v, (fa % IDX_MOD) - space_to_end, false);
	// 	else
	// 		jump_car(self, v, fa, false);
	// }
	if (fa < 0 && (mod(fa) % IDX_MOD) > PC_IND)
		jump_car(self, v,
		MEM_SIZE - (mod(fa) % IDX_MOD - PC_IND), true);
	else if (fa > 0 && fa % IDX_MOD > space_to_end)
		jump_car(self, v, (fa % IDX_MOD) - space_to_end, true);
	else
		jump_car(self, v, fa % IDX_MOD, false);
	if (self->carry == false)
		move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
