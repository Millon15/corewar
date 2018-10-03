/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:40:10 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/03 07:40:48 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		live(t_car *self, t_vm *v)
{
	int		i;

	i = -1;
	self->nb_lives++;
	self->live_cycle = I.cur_cycle;
	if (A.verbose_value & 4)
		ft_printf("P %4d | live %d\n", self->id, self->arg_val[0]);
	while (++i < v->player_amount)
		if (self->arg_val[0] == v->player[i].name)
		{
			if (A.is_ncurses)
				N->clr[PC_IND].undrln = CLR_CYCTOWAIT;
			P(i).is_alive = true;
			P(i).points = I.cur_cycle;
			P(i).lives_in_cp++;
			P(i).total_lives++;
			if (A.verbose_value & 1)
				ft_printf("Player %d (%s) is said to be alive\n"
				, i + 1, P(i).prog_name);
			break ;
		}
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
