/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:34 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/07 14:54:39 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

inline static void	verbose_zjmp(t_car *self, int val)
{
	ft_printf("P %4d | zjmp %d %s\n", self->id, val,
		(self->carry) ? "OK" : "FAILED");
}

void				zjmp(t_car *self, t_vm *v)
{
	int			f_arg;

	f_arg = obtain_argval(v, self, 0, true);
	self->carry ? move_pc(self, v, f_arg % IDX_MOD, false)
	: move_pc(self, v, self->pc_padding, false);
	if (IS_VERB(4))
		verbose_zjmp(self, f_arg);
	self->pc_padding = 0;
}
