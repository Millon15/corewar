/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 23:14:35 by akupriia          #+#    #+#             */
/*   Updated: 2018/10/19 21:33:00 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#define SR			SHORT_RANGE

long				assign_arg(long arg)
{
	if ((ft_abs(arg - SR) <= MEM_SIZE && (arg - SR) % IDX_MOD == arg % IDX_MOD
	- IDX_MOD) || ((arg % SR) > SR / 2 && (arg % SR) < SR - MEM_SIZE &&
	((arg % SR) % IDX_MOD == (arg % SR) % MEM_SIZE || ((arg % SR) - SR) %
	IDX_MOD == 0 || ((arg % SR) - SR) % MEM_SIZE == 0)) || (arg > SR / 2 && arg
	< SR - MEM_SIZE && arg % IDX_MOD >= IDX_MOD / 2 - 10 && arg % IDX_MOD
	<= IDX_MOD / 2 + 10))
		arg = arg - SR;
	else if ((((int)(arg)) % IDX_MOD == arg % IDX_MOD - IDX_MOD) ||
	((arg % SR) > SR / 2 && (arg % SR) < SR - MEM_SIZE
	&& ((arg % SR) - SR) % IDX_MOD == (arg % SR) % IDX_MOD - IDX_MOD))
		arg = (int)(arg);
	else if (!((!(arg % IDX_MOD) || !(arg % MEM_SIZE)) || (arg % SR >= FPOS &&
	arg % SR <= FPOS1) || ((arg >> 24) <= 254 && arg >> 24) || (arg % IDX_MOD
	== arg % MEM_SIZE) || (arg <= MEM_SIZE) || (arg % IDX_MOD == IDX_MOD -
	1 && arg % MEM_SIZE == MEM_SIZE - 1 && ft_abs(arg - SR) > MEM_SIZE) ||
	(ft_abs(arg % SR - SR) <= MEM_SIZE) || ((arg % SR) == (arg % MEM_SIZE)) ||
	((arg % SR - SR) % IDX_MOD == arg % IDX_MOD - IDX_MOD && ft_abs(arg - SR) >
	MEM_SIZE && arg > FPOS1) || (arg % MEM_SIZE == arg % SR && arg > SR +
	MEM_SIZE) || (((arg % MEM_SIZE) - (arg % IDX_MOD)) == IDX_MOD) || (arg >
	MEM_SIZE && arg < SR - MEM_SIZE)))
		arg = arg % IDX_MOD - IDX_MOD;
	return (arg);
}

int					set_val_neg(t_car *self, t_vm *v, long arg_sum)
{
	const unsigned int	res = self->reg[self->arg_val[0]];
	const int			size = sizeof(res);
	const unsigned int	memsz = (ft_abs(arg_sum) > PC_IND) ? MEM_SIZE : 0;
	int					i;
	int					module;

	module = arg_sum + PC_IND;
	i = -1;
	while (++i < size)
		print_arena(v->arena + (memsz + module + i) % MEM_SIZE,
		PUMPKIN, self, v);
	return (module);
}

int					set_val(t_car *self, t_vm *v, long arg_sum)
{
	const unsigned int	res = self->reg[self->arg_val[0]];
	const int			size = sizeof(res);
	unsigned char		*arena;
	int					i;
	int					module;

	arena = v->arena;
	module = PC_IND + arg_sum % IDX_MOD;
	i = -1;
	while (++i < size)
		print_arena(arena + (module + i) % MEM_SIZE, PUMPKIN, self, v);
	return (module);
}
