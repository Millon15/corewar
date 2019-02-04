/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:40:10 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/04 23:11:36 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		live(t_car *self, t_vm *v)
{
	int		i;

	i = -1;
	self->nb_lives++;
	self->live_cycle = I.cur_cycle;
	while (++i < v->player_amount)
		if (self->arg_val[0] == v->player[i].name)
		{
			if (A.is_ncurses)
				N->clr[PC_IND].undrln = CLR_CYCTOWAIT;
			P(i).is_alive = true;
			P(i).points = I.cur_cycle;
			P(i).lives_in_cp++;
			P(i).total_lives++;
			break ;
		}
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
