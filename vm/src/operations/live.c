/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:47:10 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/02 21:30:53 by akupriia         ###   ########.fr       */
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
			(v->player[i]).is_alive = true;
			(v->player[i]).points = I.cur_cycle;
			(v->player[i]).lives_in_cp++;
		}
	}
	move_pc(self, v, self->pc_padding);
	self->pc_padding = 0;
}
