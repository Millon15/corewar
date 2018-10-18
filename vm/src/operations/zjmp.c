/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:34 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/18 19:37:46 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		jump_car(t_car *self, t_vm *v, int val,
bool is_jump_car)
{
	int					res;
	int					valmints;
	const int			tmp = self->arg_val[0];

	res = (val - PC_IND > MEM_SIZE / 2) ?
	(-1 * (MEM_SIZE - val % MEM_SIZE + PC_IND)) : (val % MEM_SIZE);
	if (self->carry == true)
		move_pc(self, v, val, is_jump_car);
	valmints = tmp - SHORT_RANGE;
	if ((tmp < FPOS) || (res + SPACE_TO_END
	== tmp) || (tmp % SHORT_RANGE >= FPOS
	&& tmp % SHORT_RANGE <= SHORT_RANGE / 2) || (tmp
	% IDX_MOD == tmp % MEM_SIZE))
		res = tmp;
	else if ((tmp > MEM_SIZE && tmp
	< SHORT_RANGE && valmints % IDX_MOD == res) ||
	((tmp > MEM_SIZE) && !(tmp
	% IDX_MOD) && !(tmp % MEM_SIZE)))
		res = valmints;
	if (A.verbose_value & 4)
		ft_printf("P %4d | zjmp %d %s\n", self->id,
		tmp <= MEM_SIZE * 2
		? tmp : res, (self->carry ==
		true) ? "OK" : "FAILED");
}

void					zjmp(t_car *self, t_vm *v)
{
	int					fa;
	long				tmp;

	tmp = self->arg_val[0];
	if ((tmp > SHORT_RANGE / 2 && tmp <= SHORT_RANGE + MEM_SIZE)
	&& (tmp - SHORT_RANGE) % IDX_MOD == (tmp % IDX_MOD - IDX_MOD))
		fa = tmp - SHORT_RANGE;
	else
		fa = tmp;
	if (fa < 0 && (ft_abs(fa) % IDX_MOD) > PC_IND)
		jump_car(self, v,
		MEM_SIZE - (ft_abs(fa) % IDX_MOD - PC_IND), true);
	else if (fa > 0 && fa % IDX_MOD > SPACE_TO_END)
		jump_car(self, v, (fa % IDX_MOD) - SPACE_TO_END, true);
	else
		jump_car(self, v, fa % IDX_MOD, false);
	if (self->carry == false)
		move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
