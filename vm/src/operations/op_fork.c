/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:50:06 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/21 06:16:41 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#define FPC_IND			(pc - v->arena)
#define FPC_END			(MEM_SIZE - FPC_IND)

static unsigned char	*set_arg(long t, long *arg,
t_car *self, t_vm *v)
{
	unsigned char	*pc;

	if ((ft_abs(t - SHORT_RANGE) <= MEM_SIZE * 2 &&
	(t - SHORT_RANGE) % IDX_MOD == *arg - IDX_MOD) || (t >= SHORT_RANGE / 2
	&& (t - SHORT_RANGE) % IDX_MOD == t % IDX_MOD - IDX_MOD))
		*arg = t - SHORT_RANGE;
	else if ((t >= MEM_SIZE * 2 && t < SHORT_RANGE - MEM_SIZE) || (t %
	SHORT_RANGE >= FPOS && t % SHORT_RANGE <= FPOS1) || ((t - SHORT_RANGE) %
	IDX_MOD == t % IDX_MOD - IDX_MOD && t > FPOS1 && ft_abs(t - SHORT_RANGE)
	> MEM_SIZE * 2) || (((t % MEM_SIZE) - (t % IDX_MOD)) == IDX_MOD))
		*arg = t;
	else if (t >= MEM_SIZE * 2 && *arg && t % *arg)
		*arg -= IDX_MOD;
	else if (t % IDX_MOD == IDX_MOD / 2 &&
	ft_abs(t - SHORT_RANGE) <= MEM_SIZE * 2)
		*arg = (t - SHORT_RANGE) % IDX_MOD;
	pc = (ft_abs(*arg % IDX_MOD) > PC_IND) ? v->arena
	+ (MEM_SIZE + *arg % IDX_MOD + PC_IND) % MEM_SIZE
	: v->arena + (PC_IND + *arg % IDX_MOD) % MEM_SIZE;
	if (t % IDX_MOD == IDX_MOD / 2 && ft_abs(t -
	SHORT_RANGE) <= MEM_SIZE * 2 && (t - SHORT_RANGE)
	% IDX_MOD != t % IDX_MOD - IDX_MOD)
		pc = FPC_IND >= IDX_MOD
		? pc - IDX_MOD : pc - 0;
	return (pc);
}

static void				print_v(t_car *self, t_vm *v,
long arg, unsigned char *pc)
{
	int					pos;
	const int			tmp = self->arg_val[0];
	int					valmints;

	valmints = tmp - SHORT_RANGE;
	if ((ft_abs(tmp - SHORT_RANGE) <= MEM_SIZE * 2 &&
	(tmp - SHORT_RANGE) % IDX_MOD == arg - IDX_MOD) ||
	(tmp >= SHORT_RANGE / 2 && (tmp - SHORT_RANGE) % IDX_MOD
	== tmp % IDX_MOD - IDX_MOD))
		pos = arg;
	else
		pos = pc - self->pc;
	if (IS_VERB(4))
	{
		if (arg > 0)
			ft_printf("P %4d | fork %d (%d)\n",
			self->id, tmp, arg % IDX_MOD + PC_IND);
		else
			ft_printf("P %4d | fork %d (%d)\n", self->id, pos,
			arg % IDX_MOD + PC_IND);
	}
}

void					op_fork(t_car *self, t_vm *v)
{
	unsigned char		*pc;
	long				tmp;
	long				arg;

	arg = self->arg_val[0] % IDX_MOD;
	tmp = self->arg_val[0];
	if (tmp >= IDX_MOD)
		pc = set_arg(tmp, &arg, self, v);
	else
		pc = (arg >= SPACE_TO_END) ?
		v->arena + (arg - SPACE_TO_END) % MEM_SIZE
		: self->pc + arg;
	print_v(self, v, arg, pc);
	copy_car(self, v, pc);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
