/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:47:10 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/18 16:28:56 by akupriia         ###   ########.fr       */
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
		if (self->arg_val[0] == i)
			(v->player[i]).is_alive = 1;
	}
	self->pc = MOVE_PC(v->arena, self->pc, self->pc_padding);
	self->pc_padding = 0;
}
