/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:34 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/11 03:41:40 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		jump_car(t_car *self, t_vm *v, int val,
	bool is_jump_car)
{
	int		res;

	// 	if (MEM_SIZE - val > PC_DELTA)
	// 		res = -1 * (MEM_SIZE - val + PC_DELTA);
	// 	else
	// 		res = val;
		// res = (MEM_SIZE - val > PC_DELTA) ? (-1 * (MEM_SIZE - val + PC_DELTA)) : (val);
		// if (val - PC_DELTA > 0 && val - PC_DELTA > MEM_SIZE / 2)
		// 	res = -1 * (MEM_SIZE - val + PC_DELTA);
	res = (val - PC_DELTA > 0 && val - PC_DELTA > MEM_SIZE / 2) ?
	(-1 * (MEM_SIZE - val + PC_DELTA)) : (val);
	if (self->carry == true)
		move_pc(self, v, val, is_jump_car);
	if (v->args.verbose_value & 4)
		ft_printf("P %4d | zjmp %d %s\n", self->id, res,
		(self->carry == true) ? "OK" : "FAILED");
}

// void					zjmp(t_car *self, t_vm *v)
// {
// 	unsigned int		space_to_end;
	
// 	if (self->arg_val[0] >= IDX_MOD)
// 	{
// 		self->arg_val[0] %= IDX_MOD;
// 		if (self->arg_val[0])
// 			self->arg_val[0] -= IDX_MOD;
// 		if (mod(self->arg_val[0]) > PC_DELTA)
// 			jump_car(self, v,
// 			MEM_SIZE - (mod(self->arg_val[0]) - (PC_DELTA)), true);
// 		else
// 			jump_car(self, v, self->arg_val[0], false);
// 	}
// 	else
// 	{
// 		space_to_end = MEM_SIZE - (PC_DELTA);
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
	unsigned int		space_to_end;
	bool				fl;

	fl = false;
	space_to_end = MEM_SIZE - (PC_DELTA);
	if (self->arg_val[0] >= IDX_MOD)
	{
		self->arg_val[0] %= IDX_MOD;
		if (self->arg_val[0])
			self->arg_val[0] -= IDX_MOD;
		fl = true;
	}
	if (fl && mod(self->arg_val[0]) > PC_DELTA)
		jump_car(self, v,
		MEM_SIZE - (mod(self->arg_val[0]) - (PC_DELTA)), true);
	else if (!fl && self->arg_val[0] > space_to_end)
		jump_car(self, v, self->arg_val[0] - space_to_end, true);
	else
		jump_car(self, v, self->arg_val[0], false);
	if (self->carry == false)
		move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
