/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:28:14 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/06 20:58:56 by akupriia         ###   ########.fr       */
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
	(v->arena + find_addr(PC_IND + padding)) :
	(v->arena + find_addr(padding));
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
