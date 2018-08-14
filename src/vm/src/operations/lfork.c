/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:51:41 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/14 22:14:58 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		lfork(t_car *self, t_vm *v)
{
	unsigned char	*pc;
	t_car			tmp;

	if (self->arg_val[0] > ft_strlen((char*)self->pc))
		pc = &self->ar_start[self->arg_val[0] - ft_strlen((char*)self->pc)];
	else
		pc = &self->pc[self->arg_val[0]];
	tmp = *self;
	while (self)
		self = self->next;
	*self = tmp;
}
