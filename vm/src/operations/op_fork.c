/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:50:06 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/02 08:03:20 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#define FPC_IND	(pc - v->arena)
#define FPC_END	(MEM_SIZE - FPC_IND)

static inline unsigned char	*set_arg(long t, long *arg,
t_car *self, t_vm *v)
{
	unsigned char	*pc;

	if (mod(t - SHORT_RANGE) <= MEM_SIZE * 2 &&
	(t - SHORT_RANGE) % IDX_MOD == *arg - IDX_MOD)
		*arg = t - SHORT_RANGE;
	else if ((t >= MEM_SIZE * 2 &&
	t % IDX_MOD == t % MEM_SIZE) || (t >= FPOS && t <= FPOS1))
		*arg = t;
	else if (t >= MEM_SIZE * 2 && *arg && t % *arg)
		*arg -= IDX_MOD;
	else if (t % IDX_MOD == IDX_MOD / 2 &&
	mod(t - SHORT_RANGE) <= MEM_SIZE * 2)
		*arg = (t - SHORT_RANGE) % IDX_MOD;
	pc = (mod(*arg % IDX_MOD) > PC_IND) ? v->arena
	+ (MEM_SIZE + *arg % IDX_MOD + PC_IND) % MEM_SIZE
	: v->arena + (PC_IND + *arg % IDX_MOD) % MEM_SIZE;
	if (t % IDX_MOD == IDX_MOD / 2 && mod(t -
	SHORT_RANGE) <= MEM_SIZE * 2 && (t - SHORT_RANGE)
	% IDX_MOD != t % IDX_MOD - IDX_MOD)
		pc = FPC_IND >= IDX_MOD
		? pc - IDX_MOD : pc - 0;
	return (pc);
}

static inline void			print_v(t_car *self, t_vm *v,
long arg, unsigned char *pc)
{
	int valmints = self->arg_val[0] - SHORT_RANGE;
	if (A.verbose_value & 4)
	{
		if ((self->arg_val[0] % IDX_MOD == IDX_MOD / 2 && mod(self->arg_val[0] -
		SHORT_RANGE) <= MEM_SIZE * 2) && (valmints)
		% IDX_MOD != self->arg_val[0] % IDX_MOD - IDX_MOD)
			ft_printf("P %4d | fork %d (%d)\n", self->id,
			valmints, FPC_IND >= IDX_MOD ? (FPC_IND
			- IDX_MOD) % MEM_SIZE : FPC_IND % MEM_SIZE);
		else if (mod(valmints) <= MEM_SIZE * 2 && valmints == arg)
			ft_printf("P %4d | fork %d (%d)\n", self->id,
			arg, arg % IDX_MOD + PC_IND/*FPC_IND % MEM_SIZE*/);
		else
		{
			if (arg > 0)
				ft_printf("P %4d | fork %d (%d)\n",
				self->id, self->arg_val[0], arg % IDX_MOD + PC_IND);
			else
				ft_printf("P %4d | fork %d (%d)\n", self->id,
				(!((self->arg_val[0] % MEM_SIZE) % IDX_MOD) &&
				self->arg_val[0]) ? -IDX_MOD : pc - self->pc,
				arg % IDX_MOD + PC_IND/* % MEM_SIZE*/);
		}
	}
}

void						op_fork(t_car *self, t_vm *v)
{
	unsigned char	*pc;
	long			tmp;
	long			arg;

	arg = self->arg_val[0] % IDX_MOD;
	tmp = self->arg_val[0];
	if (I.cur_cycle == 13115 && self->id == 464)
		ft_printf("");
	if (tmp >= IDX_MOD)
		pc = set_arg(tmp, &arg, self, v);
	else
		pc = (arg > SPACE_TO_END) ?
		v->arena + (arg - SPACE_TO_END) % MEM_SIZE
		: self->pc + arg;
	print_v(self, v, arg, pc);
	copy_car(self, v, pc);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
