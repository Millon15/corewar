/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:28:14 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/14 23:56:57 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

int					mod(int x)
{
	return (x >= 0 ? x : -x);
}

static inline bool	check_pcs(t_car *self, t_vm *v)
{
	t_car	*car;

	car = v->head;
	while (car)
	{
		if (car != self)
			if (car->pc == self->pc)
				return (false);
		car = car->next;
	}
	return (true);
}

void				move_pc(t_car *self, t_vm *v, unsigned int padding,
	bool is_jump_car)
{
	unsigned char		*color_place;

	if (A.is_ncurses)
	{
		color_place = v->e->acolor + PC_IND;
		*color_place -= (*color_place >= v->e->ccolors[0] &&
		check_pcs(self, v)) ? COLOR_DELTA : 0;
	}
	self->pc = (is_jump_car == false) ?
	(v->arena + (PC_IND + padding) % MEM_SIZE) :
	(v->arena + (padding) % MEM_SIZE);
	if (A.is_ncurses)
	{
		color_place = v->e->acolor + PC_IND;
		*color_place += (*color_place < v->e->ccolors[0]) ? COLOR_DELTA : 0;
	}
}

void				print_arena(unsigned char *arena, unsigned char to_equate,
	t_car *self, t_vm *v)
{
	*arena = to_equate;
	if (A.is_ncurses)
	{
		*(v->e->acolor + (arena - v->arena)) = v->e->pcolors[PL_IND(self)];
		*(v->e->cbold + (arena - v->arena)) = START_CYCLES_PER_SEC;
	}
}
