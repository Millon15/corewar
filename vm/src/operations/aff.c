/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:52:00 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/02 06:50:39 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		aff(t_car *self, t_vm *v)
{
	if (!A.is_ncurses)
		ft_printf("%C\n", self->reg[self->arg_val[0]] % 256);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
