/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:34 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/05 23:21:19 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static void	jump_car(t_car *self, t_vm *v, int val)
{
	if (self->carry == true)
	{
		self->pc = (v->arena + (val) % MEM_SIZE);
		if (v->args.verbose_value & 4)
			ft_printf("P\t%d | zjmp %d OK\n", self->id, val);
	}
	else
		if (v->args.verbose_value & 4)
			ft_printf("P\t%d | zjmp %d FAILED\n", self->id, val);
}

static void	move_neg_val(t_car *self, t_vm *v, int val)
{
	if (self->carry == true)
	{
		self->pc = (v->arena + (self->pc - v->arena + val) % MEM_SIZE);
		if (v->args.verbose_value & 4)
			ft_printf("P\t%d | zjmp %d OK\n", self->id, val);
	}
	else
		if (v->args.verbose_value & 4)
			ft_printf("P\t%d | zjmp %d FAILED\n", self->id, val);
}

void		zjmp(t_car *self, t_vm *v)
{
	int					num;
	
	// ft_printf("I.cycle: %d | self->arg_val[0]: %d\n", I.cur_cycle, self->arg_val[0]);
	if (self->arg_val[0] >= IDX_MOD)
	{
		self->arg_val[0] %= IDX_MOD;
		if (self->arg_val[0])
			self->arg_val[0] -= IDX_MOD;
		// ft_printf("I.cycle: %d | self->arg_val[0]: %d, mod(self->arg_val[0]): %d | self->pc - v->arena %d\n", I.cur_cycle, self->arg_val[0], mod(self->arg_val[0]), self->pc - v->arena);
		// if (self->arg_val[0] > &v->arena[((int)v->player[UINT_MAX - WHOM(self)].prog_size)] - self->pc)
		if (mod(self->arg_val[0]) > self->pc - v->arena)
			jump_car(self, v, MEM_SIZE - (mod(self->arg_val[0]) - self->pc - v->arena))
			// jump_car(self, v, MEM_SIZE - mod(self->arg_val[0]) - (self->pc - v->arena));
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
			jump_car(self, v, self->arg_val[0] - (MEM_SIZE - (self->pc - v->arena)));
		else
			jump_car(self, v, self->arg_val[0]);
	self->pc_padding = 0;
}
