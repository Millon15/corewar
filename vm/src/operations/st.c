/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:40:59 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/07 01:30:02 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
// > FPOS1 || > SHORT_RANGE / 2 ?????????
static inline int	calc_fa(int tmp)
{
	int	first_arg;

	if (tmp > IDX_MOD && !(tmp % IDX_MOD))
		first_arg = 0;
	// else if (tmp == 6659)
	// 	first_arg = (tmp > IDX_MOD) ?
	// 	tmp % IDX_MOD : tmp;
	else if ((ft_abs(tmp - SHORT_RANGE) <= IDX_MOD) || ((tmp > SHORT_RANGE / 2) &&
	(tmp < SHORT_RANGE - MEM_SIZE * 2) && (tmp % IDX_MOD == tmp % MEM_SIZE)) ||
	(ft_abs(tmp - SHORT_RANGE) <= IDX_MOD))
		first_arg = tmp - SHORT_RANGE;
	// else if (((tmp > SHORT_RANGE / 2) && (tmp % IDX_MOD == tmp % MEM_SIZE)
	// && (tmp - SHORT_RANGE) % IDX_MOD == tmp % IDX_MOD - IDX_MOD) ||
	// ((tmp > SHORT_RANGE / 2 && tmp < SHORT_RANGE - MEM_SIZE) && 
	// (tmp - SHORT_RANGE) % IDX_MOD == tmp % IDX_MOD - IDX_MOD))
	else if ((tmp > SHORT_RANGE / 2 && tmp <= SHORT_RANGE && tmp % IDX_MOD == IDX_MOD / 2)
	|| (tmp % SHORT_RANGE >= FPOS && tmp % SHORT_RANGE <= SHORT_RANGE / 2) || (tmp > MEM_SIZE && tmp <= MEM_SIZE * 2/* && (tmp % MEM_SIZE >= MEM_SIZE / 2)*/) || ((ft_abs(tmp - SHORT_RANGE) <= MEM_SIZE * 2)
	&& (tmp % IDX_MOD == tmp % MEM_SIZE))/* || (tmp == 16962)*/)
	{
		// first_arg = (tmp > MEM_SIZE) ?
		// tmp % IDX_MOD - IDX_MOD : tmp % IDX_MOD;
		first_arg = (tmp > IDX_MOD) ?
		tmp % IDX_MOD : tmp;
		if (tmp > MEM_SIZE && !(tmp % SHORT_RANGE >= FPOS && tmp % SHORT_RANGE <= SHORT_RANGE / 2) && !(tmp > MEM_SIZE && tmp <= MEM_SIZE * 2)/* && (tmp != 16962)*/)
			first_arg -= IDX_MOD;
	}
	else if (/*(tmp > MEM_SIZE && tmp < MEM_SIZE * 2)
	|| */(tmp % IDX_MOD == tmp % MEM_SIZE)
	|| (tmp > MEM_SIZE * 2 && tmp < FPOS) || (tmp > SHORT_RANGE / 2 && tmp < SHORT_RANGE - MEM_SIZE * 2) ||
	((tmp > IDX_MOD) && (tmp <= MEM_SIZE) && !(tmp % IDX_MOD)) ||
	((tmp > MEM_SIZE * 2) && !(tmp % IDX_MOD) && ((tmp % MEM_SIZE) <= MEM_SIZE / 2)
	&& (!((tmp % MEM_SIZE) % IDX_MOD))))
	/*|| (ft_abs(tmp - SHORT_RANGE) <= MEM_SIZE && (ft_abs(tmp - SHORT_RANGE) <= IDX_MOD)
	&& (tmp - SHORT_RANGE) % IDX_MOD != tmp % IDX_MOD - IDX_MOD)*/
		first_arg = tmp;
	else
	{
		first_arg = (tmp > MEM_SIZE) ?
		tmp % IDX_MOD - IDX_MOD : tmp % IDX_MOD;
		// if (tmp > MEM_SIZE)
		// 	first_arg -= IDX_MOD;
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
	first_arg %= MEM_SIZE;
	if (first_arg == IDX_MOD)
		pc_index = PC_IND;
	else
	{
		// if (first_arg >= 0 && first_arg >= SPACE_TO_END)
		// {
		// 	// if ((PC_IND + first_arg % MEM_SIZE) < MEM_SIZE)
		// 		pc_index = first_arg - SPACE_TO_END;
		// }
		if (first_arg >= 0 && first_arg >= SPACE_TO_END)
		{
			// if ((PC_IND + first_arg % MEM_SIZE) < MEM_SIZE)
			if (first_arg - SPACE_TO_END >= MEM_SIZE / 2 && first_arg % IDX_MOD <= SPACE_TO_END)
				pc_index = first_arg % IDX_MOD + SPACE_TO_END;
			else if (first_arg - SPACE_TO_END >= MEM_SIZE / 2)
				pc_index = MEM_SIZE + first_arg % IDX_MOD + SPACE_TO_END;
			else
				pc_index = MEM_SIZE + first_arg + PC_IND;
				// pc_index = first_arg - SPACE_TO_END;
		}
		else if (first_arg < 0 && ft_abs(first_arg) > PC_IND)
		{
			if (ft_abs(first_arg) - PC_IND >= MEM_SIZE / 2 && ft_abs(first_arg % IDX_MOD) <= PC_IND)
				pc_index = first_arg % IDX_MOD + PC_IND;
			else if (ft_abs(first_arg) - PC_IND >= MEM_SIZE / 2)
				pc_index = MEM_SIZE + first_arg % IDX_MOD + PC_IND;
			else
				pc_index = MEM_SIZE + first_arg + PC_IND;
		}
		else
			pc_index = first_arg + PC_IND;
	}
	while (++i < 4)
		print_arena(v->arena + (pc_index + i) % MEM_SIZE, PUMPKIN, self, v);
}

static inline void	alter_for_verbose(int tmp, int *first_arg)
{
	if ((tmp > SHORT_RANGE / 2 && tmp <= SHORT_RANGE
	&& tmp % IDX_MOD == IDX_MOD / 2) || (tmp > MEM_SIZE && !(tmp % IDX_MOD)
	&& !(tmp % MEM_SIZE)) || (ft_abs(tmp - SHORT_RANGE) <= MEM_SIZE && (tmp - SHORT_RANGE) % IDX_MOD
	== tmp % IDX_MOD - IDX_MOD) || ((ft_abs(tmp >= SHORT_RANGE) <= MEM_SIZE * 2) //(tmp >= SHORT_RANGE - MEM_SIZE * 2) ?
	&& (tmp % IDX_MOD == tmp % MEM_SIZE)) || (ft_abs(tmp - SHORT_RANGE) <= MEM_SIZE * 2))
		*first_arg = tmp - SHORT_RANGE;
	else if ((tmp > IDX_MOD && tmp <= MEM_SIZE && !(tmp % IDX_MOD)) || (tmp > MEM_SIZE && tmp <= MEM_SIZE * 2)
	|| (tmp > MEM_SIZE && !(tmp % IDX_MOD) && (tmp % MEM_SIZE) <= MEM_SIZE / 2
	&& !((tmp % MEM_SIZE) % IDX_MOD)) || (tmp % SHORT_RANGE >= FPOS && tmp % SHORT_RANGE <= FPOS1))
		*first_arg = tmp;
	
}

void				st(t_car *self, t_vm *v)
{
	unsigned char		*pc;
	int					first_arg;
	const unsigned int	res = self->reg[self->arg_val[0]];
	const unsigned int	size = sizeof(res);
	int					tmp;

	// if (self->id == 52 && I.cur_cycle == 7256)
	// 	ft_printf("");
	if (I.cur_cycle == 11914)
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
	if (A.verbose_value/* && I.cur_cycle != 2719*/)
	{
		ft_printf("P %4d | st r%d %d\n", self->id, self->arg_val[0],
		(tmp <= MEM_SIZE) ? tmp : first_arg);
	}
		
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
