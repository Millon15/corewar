/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:52:00 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/23 20:00:41 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		aff(t_car *self, t_vm *v)
{
	ft_printf("%c\n", self->reg[self->arg_val[0]] % 256);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
