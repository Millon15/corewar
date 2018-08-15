/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:56:16 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/15 22:26:40 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

#define I				v->info

static inline void		do_all_stuff(t_vm *v)
{
	I.cycle_to_die = CYCLE_TO_DIE;
	while (I.cycle_to_die > 0)
	{
		if (v->args.is_dump && v->args.dump_value == I.cur_cycle)
			dump_arena(v);
		I.cur_car = v->head;
		while (I.cur_car)
		{
			I.cur_car->perform_next_comm(I.cur_car, v);
			I.cur_car = I.cur_car->next;
		}
		if ((nbr_live_exec(v->head)) || (MAX_CHECKS * I.cycle_to_die <= I.cur_cycle))
		{
			ft_printf("%d\n", v->head->nb_lives);
			I.cycle_to_die -= CYCLE_DELTA;
			make_live_nil(v->head);
		}
		I.cur_cycle++;
	}
}

int						main(int ac, char **av)
{
	t_vm		v;

	ft_bzero(&v, sizeof(v));
	check_and_obtain_args(ac, av, &v);
	fill_players(&v);
	fill_arena(&v);
	do_all_stuff(&v);
	return (0);
}
