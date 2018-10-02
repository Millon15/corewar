/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:34 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/02 09:23:02 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		jump_car(t_car *self, t_vm *v, int val,
bool is_jump_car)
{
	int					res;
	int					valmints;

	res = (val - PC_IND > MEM_SIZE / 2) ?
	(-1 * (MEM_SIZE - val + PC_IND)) : (val);
	if (self->carry == true)
		move_pc(self, v, val, is_jump_car);
	valmints = self->arg_val[0] - SHORT_RANGE;
	if ((self->arg_val[0] < FPOS/* || self->arg_val[0]
	% MEM_SIZE <= MEM_SIZE / 2*/) || (res + SPACE_TO_END
	== self->arg_val[0]) || (self->arg_val[0] % SHORT_RANGE >= FPOS
	&& self->arg_val[0] % SHORT_RANGE <= FPOS1) || (self->arg_val[0]
	% IDX_MOD == self->arg_val[0] % MEM_SIZE))
		res = self->arg_val[0];
	else if ((self->arg_val[0] > MEM_SIZE && self->arg_val[0]
	< SHORT_RANGE && valmints % IDX_MOD == res) ||
	((self->arg_val[0] > MEM_SIZE) && !(self->arg_val[0]
	% IDX_MOD) && !(self->arg_val[0] % MEM_SIZE)))
		res = valmints;
	if (A.verbose_value & 4)
		ft_printf("P %4d | zjmp %d %s\n", self->id,
		self->arg_val[0] <= MEM_SIZE * 2
		? self->arg_val[0] : res, (self->carry ==
		true) ? "OK" : "FAILED");
}

void					zjmp(t_car *self, t_vm *v)
{
	bool				fl;
	int					fa;
	int					tmp;

	if (I.cur_cycle == 10926)
		ft_printf("");
	tmp = self->arg_val[0];
	if (ft_abs(tmp - SHORT_RANGE) <= MEM_SIZE
	&& (tmp - SHORT_RANGE) % IDX_MOD == (tmp % IDX_MOD - IDX_MOD))
		fa = tmp - SHORT_RANGE;
	else if (tmp > FPOS && tmp
	% MEM_SIZE > MEM_SIZE / 2)
		fa = tmp % IDX_MOD - IDX_MOD;
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
