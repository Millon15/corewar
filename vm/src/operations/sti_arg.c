/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 23:14:35 by akupriia          #+#    #+#             */
/*   Updated: 2018/10/16 23:15:56 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

int		set_val_neg(t_car *self, t_vm *v, long arg_sum)
{
	const unsigned int	res = self->reg[self->arg_val[0]];
	const unsigned int	size = sizeof(res);
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

int		set_val(t_car *self, t_vm *v, long arg_sum)
{
	const unsigned int	res = self->reg[self->arg_val[0]];
	const unsigned int	size = sizeof(res);
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
