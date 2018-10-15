/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:50:06 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/15 19:15:08 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#define FPC_IND	(pc - v->arena)
#define FPC_END	(MEM_SIZE - FPC_IND)

static inline unsigned char	*set_arg(long t, long *arg,
t_car *self, t_vm *v)
{
	unsigned char	*pc;

	if ((ft_abs(t - SHORT_RANGE) <= MEM_SIZE * 2 &&
	(t - SHORT_RANGE) % IDX_MOD == *arg - IDX_MOD) || (t >= SHORT_RANGE / 2
	&& (t - SHORT_RANGE) % IDX_MOD == t % IDX_MOD - IDX_MOD))
		*arg = t - SHORT_RANGE;
	else if ((t >= MEM_SIZE * 2 && t < SHORT_RANGE - MEM_SIZE
	/*t % IDX_MOD == t % MEM_SIZE*/) || (t % SHORT_RANGE >= FPOS && t
	% SHORT_RANGE <= FPOS1) || ((t - SHORT_RANGE) % IDX_MOD == t %
	IDX_MOD - IDX_MOD && t > FPOS1 && ft_abs(t - SHORT_RANGE) > MEM_SIZE) //t > SHORT_RANGE / 2 ?
	|| (((t % MEM_SIZE) - (t % IDX_MOD)) == IDX_MOD))
		*arg = t;
	else if (t >= MEM_SIZE * 2 && *arg && t % *arg)
		*arg -= IDX_MOD;
	else if (t % IDX_MOD == IDX_MOD / 2 &&
	ft_abs(t - SHORT_RANGE) <= MEM_SIZE * 2)
		*arg = (t - SHORT_RANGE) % IDX_MOD;
	// if (t > IDX_MOD && !(t % IDX_MOD))
	// 	*arg = 0;
	// else if ((ft_abs(t - SHORT_RANGE) <= IDX_MOD) || ((t > SHORT_RANGE / 2) &&
	// (t < SHORT_RANGE - MEM_SIZE * 2) && (t % IDX_MOD == t % MEM_SIZE)) ||
	// (ft_abs(t - SHORT_RANGE) <= IDX_MOD))
	// 	*arg = t - SHORT_RANGE;
	// // else if (((t > SHORT_RANGE / 2) && (t % IDX_MOD == t % MEM_SIZE)
	// // && (t - SHORT_RANGE) % IDX_MOD == t % IDX_MOD - IDX_MOD) ||
	// // ((t > SHORT_RANGE / 2 && t < SHORT_RANGE - MEM_SIZE) && 
	// // (t - SHORT_RANGE) % IDX_MOD == t % IDX_MOD - IDX_MOD))
	// else if ((t > SHORT_RANGE / 2 && t <= SHORT_RANGE && t % IDX_MOD == IDX_MOD / 2)
	// || (t % SHORT_RANGE >= FPOS && t % SHORT_RANGE <= FPOS1) || ((ft_abs(t - SHORT_RANGE) <= MEM_SIZE * 2)
	// && (t % IDX_MOD == t % MEM_SIZE))/* || (t == 16962)*/)
	// {
	// 	*arg = (t > IDX_MOD) ?
	// 	t % IDX_MOD : t;
	// 	if (t > MEM_SIZE && !(t % SHORT_RANGE >= FPOS && t % SHORT_RANGE <= FPOS1)/* && (t != 16962)*/)
	// 		*arg -= IDX_MOD;
	// }
	// else if ((t > MEM_SIZE && t <= MEM_SIZE * 2)
	// || (t % IDX_MOD == t % MEM_SIZE)
	// || (t > MEM_SIZE * 2 && t < FPOS) || (t > SHORT_RANGE / 2 && t < SHORT_RANGE - MEM_SIZE * 2) ||
	// ((t > IDX_MOD) && (t <= MEM_SIZE) && !(t % IDX_MOD)) ||
	// ((t > MEM_SIZE * 2) && !(t % IDX_MOD) && ((t % MEM_SIZE) <= MEM_SIZE / 2)
	// && (!((t % MEM_SIZE) % IDX_MOD))))
	// /*|| (ft_abs(t - SHORT_RANGE) <= MEM_SIZE && (ft_abs(t - SHORT_RANGE) <= IDX_MOD)
	// && (t - SHORT_RANGE) % IDX_MOD != t % IDX_MOD - IDX_MOD)*/
	// 	*arg = t;
	// else
	// {
	// 	*arg = (t > MEM_SIZE) ?
	// 	t % IDX_MOD - IDX_MOD : t % IDX_MOD;
	// 	// if (t > MEM_SIZE)
	// 	// 	*arg -= IDX_MOD;
	// }
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

static inline void			print_v(t_car *self, t_vm *v,
long arg, unsigned char *pc)
{
	int			pos;
	const int	tmp = self->arg_val[0];
	int			valmints;

	valmints = tmp - SHORT_RANGE;
	if ((ft_abs(tmp - SHORT_RANGE) <= MEM_SIZE * 2 &&
	(tmp - SHORT_RANGE) % IDX_MOD == arg - IDX_MOD) || (tmp >= SHORT_RANGE / 2
	&& (tmp - SHORT_RANGE) % IDX_MOD == tmp % IDX_MOD - IDX_MOD))
		pos = arg;
	else
		pos = pc - self->pc;
	if (A.verbose_value & 4)
	{
	// 	if ((tmp % IDX_MOD == IDX_MOD / 2 && ft_abs(tmp -
	// 	SHORT_RANGE) <= MEM_SIZE * 2) && (valmints)
	// 	% IDX_MOD != tmp % IDX_MOD - IDX_MOD)
	// 		ft_printf("P %4d | fork %d (%d)\n", self->id,
	// 		valmints, FPC_IND >= IDX_MOD ? (FPC_IND
	// 		- IDX_MOD) % MEM_SIZE : FPC_IND % MEM_SIZE);
	// 	else if (ft_abs(valmints) <= MEM_SIZE * 2 && valmints == arg)
	// 		ft_printf("P %4d | fork %d (%d)\n", self->id,
	// 		arg, arg % IDX_MOD + PC_IND/*FPC_IND % MEM_SIZE*/);
	// 	else
	// 	{
			if (arg > 0)
				ft_printf("P %4d | fork %d (%d)\n",
				self->id, tmp, arg % IDX_MOD + PC_IND);
			else
				ft_printf("P %4d | fork %d (%d)\n", self->id,
				/*(!((tmp % MEM_SIZE) % IDX_MOD) &&
				tmp) ? -IDX_MOD : */pos,
				arg % IDX_MOD + PC_IND/* % MEM_SIZE*/);
		// }
	}
}

void						op_fork(t_car *self, t_vm *v)
{
	unsigned char	*pc;
	long			tmp;
	long			arg;
	int				new_pc;

	// new_pc = (self->pc - v->arena) + (self->arg_val[0] % IDX_MOD);
	// while (new_pc < 0)
	// 	new_pc += MEM_SIZE;
	// new_pc = new_pc % MEM_SIZE;
	arg = self->arg_val[0] % IDX_MOD;
	tmp = self->arg_val[0];
	if (I.cur_cycle == 5189 && self->id == 5)
		ft_printf("");
	if (tmp >= IDX_MOD)
		pc = set_arg(tmp, &arg, self, v);
	else
		pc = (arg >= SPACE_TO_END) ?
		v->arena + (arg - SPACE_TO_END) % MEM_SIZE
		: self->pc + arg;
	// pc = v->arena + new_pc;q
	print_v(self, v, arg, pc);
	copy_car(self, v, pc);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
