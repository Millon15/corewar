/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:56:16 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/13 20:56:59 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		do_all_stuff(t_vm *v)
{
	t_car			*cur_car;
	int				cycle_to_die;

	cycle_to_die = CYCLE_TO_DIE;
	while (cycle_to_die > 0)
	{
		cur_car = v->head;
		while (cur_car)
		{
			cur_car->perform_next_comm(cur_car, v);
			cur_car = cur_car->next;
		}
		// if ()
			cycle_to_die -= CYCLE_DELTA;
	}
}

int						main(int ac, char **av)
{
	t_vm		v;

	ft_bzero(&v, sizeof(v));
	check_and_obtain_args(ac, av, &v);
	fill_players(&v);
	fill_arena(&v);
	// print_arena_to_stdout(&v); // debug
	do_all_stuff(&v);
	return (0);
}
