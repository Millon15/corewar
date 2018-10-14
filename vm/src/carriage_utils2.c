/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:28:14 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/15 00:40:01 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

int					ft_abs(int x)
{
	return (x >= 0 ? x : -x);
}

void				move_pc(t_car *self, t_vm *v, unsigned int padding,
	bool is_jump_car)
{
	if (A.is_ncurses)
		N->clr[PC_IND].main -=
		(N->clr[PC_IND].main >= N->ccolors[0]) ? COLOR_DELTA : 0;
	self->pc = (is_jump_car == false) ?
	(v->arena + (PC_IND + padding) % MEM_SIZE) :
	(v->arena + padding % MEM_SIZE);
	if (A.is_ncurses)
		N->clr[PC_IND].main +=
		(N->clr[PC_IND].main < N->ccolors[0]) ? COLOR_DELTA : 0;
}

void				print_arena(unsigned char *arena, unsigned char to_equate,
	t_car *self, t_vm *v)
{
	*arena = to_equate;
	if (A.is_ncurses)
	{
		N->clr[arena - v->arena].main = N->pcolors[PL_IND(self)];
		N->clr[arena - v->arena].bold = CLR_CYCTOWAIT;
	}
}
