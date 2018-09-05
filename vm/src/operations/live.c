/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:47:10 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/05 20:40:31 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		live(t_car *self, t_vm *v)
{
	int i;

	i = -1;
	self->nb_lives++;
	self->live_cycle = I.cur_cycle;
	while (++i < v->player_amount)
	{
		if (self->arg_val[0] == v->player[i].name)
		{
			P(i).is_alive = true;
			P(i).points = I.cur_cycle;
			P(i).lives_in_cp++;
		}
	}
	move_pc(self, v, self->pc_padding);
	self->pc_padding = 0;
}
