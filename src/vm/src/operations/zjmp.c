/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:34 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/25 23:28:53 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static void	jump_car(t_car *self, t_vm *v, int val)
{
	self->pc = (v->arena + (val) % MEM_SIZE);
}

static void	move_neg_val(t_car *self, t_vm *v, int val)
{
	self->pc = (v->arena + (self->pc - v->arena + val) % MEM_SIZE);	
}

void		zjmp(t_car *self, t_vm *v)
{
	int					num;
	
	if (self->carry == false)
	{
		move_pc(self, v, self->pc_padding);		
		return ;
	}
	if (self->arg_val[0] >= IDX_MOD)
	{
		self->arg_val[0] %= IDX_MOD;
		if (self->arg_val[0])
			self->arg_val[0] -= IDX_MOD;
		// if (self->arg_val[0] > &v->arena[((int)v->player[UINT_MAX - WHOM(self)].prog_size)] - self->pc)
		if (MOD(self->arg_val[0]) > self->pc - v->arena)
			move_pc(self, v, self->pc_padding);
			// jump_car(self, v, MEM_SIZE - MOD(self->arg_val[0]) - (self->pc - v->arena));
		else
		{
			move_neg_val(self, v, self->arg_val[0]);
			// if (self->arg_val[0] > MEM_SIZE - (self->pc - v->arena))
			// 	self->pc = &v->arena[self->arg_val[0] - MEM_SIZE - (self->pc - v->arena)];
			// else
			// 	self->pc += self->arg_val[0];
		}
	}
	else
		if (self->arg_val[0] > MEM_SIZE - (self->pc - v->arena))
			jump_car(self, v, self->arg_val[0]);
		else
			move_pc(self, v, self->arg_val[0]);
	self->pc_padding = 0;
}
