/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:40:36 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/03 17:56:40 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline int	calc_fa(int tmp)
{
	int	first_arg;

	if (tmp > IDX_MOD && !(tmp % IDX_MOD))
		first_arg = 0;
	else if ((tmp > SHORT_RANGE / 2) && (tmp % IDX_MOD == tmp % MEM_SIZE)
	&& (tmp - SHORT_RANGE) % IDX_MOD == tmp % IDX_MOD - IDX_MOD)
		first_arg = tmp - SHORT_RANGE;
	else if ((tmp > IDX_MOD && tmp > MEM_SIZE && tmp <= MEM_SIZE * 2)
	|| (tmp % IDX_MOD == tmp % MEM_SIZE) || (tmp % SHORT_RANGE >= FPOS && tmp % SHORT_RANGE <= FPOS1)
	|| (tmp > MEM_SIZE && tmp < FPOS && (tmp - SHORT_RANGE) % IDX_MOD ==
	tmp % IDX_MOD - IDX_MOD) || ((tmp - SHORT_RANGE) % IDX_MOD ==
	tmp % IDX_MOD - IDX_MOD && tmp > SHORT_RANGE / 2 && ft_abs(tmp - SHORT_RANGE) > MEM_SIZE))
		first_arg = tmp;
	else
	{
		first_arg = (tmp > IDX_MOD) ?
		tmp % IDX_MOD : tmp;
		if (tmp > MEM_SIZE)
			first_arg -= IDX_MOD;
	}
	return (first_arg);
}

void		ld(t_car *self, t_vm *v)
{
	unsigned char	*pc;
	long			tmp;
	long			first_arg;

	if (self->id == 15 && I.cur_cycle == 2146)
		ft_printf("");
	tmp = self->arg_val[0];
	if (self->args[0] == T_DIR)
		self->reg[self->arg_val[1]] = tmp;
	else if (self->args[0] == T_IND)
	{
		// if (ft_abs(tmp - SHORT_RANGE) )
		first_arg = calc_fa(tmp);
		first_arg %= IDX_MOD;
		if (first_arg > MEM_SIZE - PC_IND)
			pc = &v->arena[first_arg - (MEM_SIZE - PC_IND)];
		else if (first_arg < 0 && ft_abs(first_arg) > PC_IND)
			pc = &v->arena[PC_IND + first_arg + MEM_SIZE];
		else
			pc = &v->arena[PC_IND + first_arg];
		self->reg[self->arg_val[1]] = get_raw_num(pc, REG_SIZE, v);
	}
	self->carry = self->reg[self->arg_val[1]] ? false : true;
	if (A.verbose_value & 4)
		ft_printf("P %4d | ld %d r%d\n", self->id,
		self->reg[self->arg_val[1]], self->arg_val[1]);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
