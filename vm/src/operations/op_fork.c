/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:50:06 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/30 08:07:09 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
# define FPC_IND	(pc - v->arena)
# define FPC_END	(MEM_SIZE - FPC_IND)

void		op_fork(t_car *self, t_vm *v)
{
	const int		space_to_end = MEM_SIZE - PC_IND;
	unsigned char	*pc;
	int				tmp;
	int				arg;

	if (self->id == 7 && I.cur_cycle > 4900)
		ft_printf("");
	arg = self->arg_val[0] % IDX_MOD;
	tmp = self->arg_val[0];
	if (self->arg_val[0] >= IDX_MOD)
	{
		// if (arg >= IDX_MOD / 2)
		if (mod(self->arg_val[0] - SHORT_RANGE) <= MEM_SIZE && (tmp - SHORT_RANGE) % IDX_MOD == arg - IDX_MOD)
			arg = tmp - SHORT_RANGE;
			// ft_printf("");
		else if (tmp >= MEM_SIZE * 2 && tmp % IDX_MOD == tmp % MEM_SIZE)
			arg = tmp;
		else if (tmp > MEM_SIZE * 2 && arg && tmp % arg) // or tmp % IDX_MOD, (which is arg) == tmp % MEM_SIZE
			arg -= IDX_MOD;
		else if (tmp % IDX_MOD == IDX_MOD / 2 && mod(tmp - SHORT_RANGE) <= MEM_SIZE)		
			arg = (tmp - SHORT_RANGE) % IDX_MOD;
		pc = (mod(arg % IDX_MOD) > PC_IND) ?
		v->arena + (MEM_SIZE + arg % IDX_MOD + PC_IND) % MEM_SIZE
		: v->arena + (PC_IND + arg % IDX_MOD) % MEM_SIZE;
		if (self->arg_val[0] % IDX_MOD == IDX_MOD / 2 && mod(self->arg_val[0] - SHORT_RANGE) <= MEM_SIZE
		&& (tmp - SHORT_RANGE) % IDX_MOD != tmp % IDX_MOD - IDX_MOD)		
			pc = FPC_IND >= IDX_MOD ? pc - IDX_MOD : pc - 0;
		// else if (mod(self->arg_val[0] - SHORT_RANGE) <= MEM_SIZE && tmp - SHORT_RANGE == arg)
		// 	pc = FPC_END >= IDX_MOD ? pc + IDX_MOD : pc + 0;
	}
	else
		pc = (arg > space_to_end) ?
		v->arena + (arg - space_to_end) % MEM_SIZE
		: self->pc + arg;
	if (A.verbose_value & 4)
	{
		if ((self->arg_val[0] % IDX_MOD == IDX_MOD / 2 && mod(self->arg_val[0] - SHORT_RANGE) <= MEM_SIZE)
		&& (tmp - SHORT_RANGE) % IDX_MOD != tmp % IDX_MOD - IDX_MOD)
			ft_printf("P %4d | fork %d (%d)\n", self->id, self->arg_val[0] - SHORT_RANGE,
			FPC_IND >= IDX_MOD ? (FPC_IND - IDX_MOD) % MEM_SIZE : FPC_IND % MEM_SIZE);
		else if (mod(self->arg_val[0] - SHORT_RANGE) <= MEM_SIZE && tmp - SHORT_RANGE == arg)
			ft_printf("P %4d | fork %d (%d)\n", self->id, arg, FPC_IND % MEM_SIZE);
		else
			arg > 0 ? ft_printf("P %4d | fork %d (%d)\n", self->id, self->arg_val[0], FPC_IND % MEM_SIZE)
			: ft_printf("P %4d | fork %d (%d)\n", self->id, !((self->arg_val[0] % MEM_SIZE) % IDX_MOD) && self->arg_val[0]
			? -IDX_MOD : pc - self->pc, FPC_IND % MEM_SIZE);
	}
	copy_car(self, v, pc);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
