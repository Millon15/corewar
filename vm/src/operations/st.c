/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:47:59 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/30 16:13:03 by akupriia         ###   ########.fr       */
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
	|| (tmp % IDX_MOD == tmp % MEM_SIZE) || (tmp >= FPOS && tmp <= FPOS1)
	|| (tmp > MEM_SIZE && tmp < FPOS
	&& (tmp - SHORT_RANGE) % IDX_MOD == tmp % IDX_MOD - IDX_MOD))
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

static inline void	output_to_arena(int first_arg, t_car *self, t_vm *v)
{
	int					i;
	int					pc_index;
	const unsigned int	res = self->reg[self->arg_val[0]];
	const unsigned int	size = sizeof(res);

	i = -1;
	if (first_arg == IDX_MOD)
		pc_index = PC_IND;
	else
	{
		if (first_arg >= 0 && first_arg > SPACE_TO_END)
			pc_index = PC_IND + first_arg % IDX_MOD;
		else if (first_arg < 0 && mod(first_arg) > PC_IND)
			pc_index = MEM_SIZE + first_arg + PC_IND;
		else
			pc_index = first_arg % MEM_SIZE + PC_IND;
	}
	while (++i < 4)
		print_arena(v->arena + (pc_index + i) % MEM_SIZE, PUMPKIN, self, v);
}

static inline void	alter_for_verbose(int tmp, int *first_arg)
{
	if ((tmp > SHORT_RANGE / 2 && tmp <= SHORT_RANGE
	&& tmp % IDX_MOD == IDX_MOD / 2) || (tmp > MEM_SIZE && !(tmp % IDX_MOD)
	&& !(tmp % MEM_SIZE)))
		*first_arg = tmp - SHORT_RANGE;
	else if ((tmp > IDX_MOD && tmp <= MEM_SIZE && !(tmp % IDX_MOD)) ||
	(tmp > MEM_SIZE && !(tmp % IDX_MOD) && (tmp % MEM_SIZE) <= MEM_SIZE / 2
	&& !((tmp % MEM_SIZE) % IDX_MOD)))
		*first_arg = tmp;
	else if (tmp > MEM_SIZE && !(tmp % IDX_MOD))
		*first_arg -= IDX_MOD;
}

void				st(t_car *self, t_vm *v)
{
	unsigned char		*pc;
	int					first_arg;
	const unsigned int	res = self->reg[self->arg_val[0]];
	const unsigned int	size = sizeof(res);
	int					tmp;

	if (self->id == 1 && I.cur_cycle == 6250)
		ft_printf("");
	tmp = self->arg_val[1];
	if (self->args[1] == T_IND)
	{
		first_arg = calc_fa(tmp);
		output_to_arena(first_arg, self, v);
		alter_for_verbose(tmp, &first_arg);
	}
	else if (self->args[1] == T_REG)
		self->reg[tmp] = res;
	if (A.verbose_value & 4)
		ft_printf("P %4d | st r%d %d\n", self->id, self->arg_val[0],
		(tmp <= MEM_SIZE) ? tmp : first_arg);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
