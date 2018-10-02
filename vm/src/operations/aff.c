/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:52:00 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/02 06:22:25 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		aff(t_car *self, t_vm *v)
{
	// if (!A.is_ncurses)
	// 	ft_printf("%C\n", self->reg[self->arg_val[0]] % IDX_MOD / 2);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
