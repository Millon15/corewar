/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:28:14 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/06 19:23:33 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

int				mod(int x)
{
	return (x >= 0 ? x : -x);
}

void			move_pc(t_car *self, t_vm *v, unsigned int padding,
	bool is_jump_car)
{
	unsigned char		*color_place;

	if (v->args.is_ncurses)
	{
		color_place = v->e->acolor + (int)(self->pc - v->arena);
		*color_place -= COLOR_DELTA;
	}
	self->pc = (is_jump_car == false) ?
	(v->arena + (self->pc - v->arena + padding) % MEM_SIZE) :
	(v->arena + (padding) % MEM_SIZE);
	if (v->args.is_ncurses)
	{
		color_place = v->e->acolor + (int)(self->pc - v->arena);
		*color_place += COLOR_DELTA;
	}
}

void			print_arena(t_car *self, t_vm *v)
{

}
