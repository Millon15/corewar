/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:55 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/23 18:34:35 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

// int				determ_size(unsigned int val)
// {
// 	int i;

// 	i = 0;
// 	while (val)
// 	{
// 		i++;		
// 		val /= 256;
// 	}
// 	return (i);
// }

static void		set_value(t_car *self, t_vm *v, int arg_sum)
{
	int		ind;
	// int		size;
	
	ind = -1;
	// size = determ_size(self->reg[T_REG]);
	if (MOD(arg_sum) > self->pc - v->arena)
	{
		while (++ind < 4)
		{
			v->arena[MEM_SIZE + arg_sum - (self->pc - v->arena) + ind] = (self->reg[self->arg_val[0]] << ind * 2) >> 6;     //??????????????????????????
			// v->color[MEM_SIZE + arg_sum - (self->pc - v->arena) + ind] = v->player[UINT_MAX - self->whom].color;
		}
	}
	else
	{
		while (++ind < 4)
		{
			v->arena[self->pc - v->arena + arg_sum + ind] = (self->reg[self->arg_val[0]] << ind * 2) >> 6;
			// v->color[self->pc - v->arena + arg_sum + ind] = v->player[UINT_MAX - self->whom].color;
		}
	}
}

void			sti(t_car *self, t_vm *v)
{
	unsigned char	*pc;
	int				arg_sum;

	if (self->args[1] == T_IND)
	{
		self->arg_val[1] %= IDX_MOD;
		if (self->arg_val[1] > MEM_SIZE - (self->pc - v->arena))
			pc = &v->arena[self->arg_val[1] - MEM_SIZE - (self->pc - v->arena)];
		else
			pc = &self->pc[self->arg_val[1]];
		arg_sum = get_raw_num(pc, 4) + self->arg_val[2];
	}
	else
		arg_sum = self->arg_val[1] + self->arg_val[2];
	arg_sum %= IDX_MOD;	
	arg_sum -= IDX_MOD;
	set_value(self, v, arg_sum);
	int i = arg_sum;
	// ft_printf("STI_pc reg_value is: %0.2x\n", self->reg[self->arg_val[0]]);
	// ft_printf("STI_pc is: ");
	// while (i < arg_sum + 10)
	// 	ft_printf("%0.2x ", self->pc[i++]);
	// ft_putchar('\n');
	move_pc(self, v, self->pc_padding);
	self->pc_padding = 0;
}
