/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:47:10 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/19 19:41:57 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		live(t_car *self, t_vm *v)
{
	int i;

	i = -1;
	self->nb_lives++;
	while (++i < v->player_amount)
	{
		if (self->arg_val[0] == v->player[i].name)
		{
			(v->player[i]).is_alive = 1;
			(v->player[i]).points = I.cur_cycle;
			(v->player[i]).lives_in_cp++;
		}
	}
	self->pc = MOVE_PC(v->arena, self->pc, self->pc_padding);
	self->pc_padding = 0;
}
