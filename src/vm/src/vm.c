/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:56:16 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/07 19:53:29 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		do_all_stuff(t_vm *v)
{
	t_car			*tmp;
	unsigned int	cycle_to_die;

	cycle_to_die = CYCLE_TO_DIE;
	while (cycle_to_die > 0)
	{
		tmp = v->head;
		while (tmp)
		{
			tmp->vt.perform_next_comm(&tmp);
			tmp = tmp->next;
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
	// do_all_stuff(&v);
	print_arena_to_stdout(&v); // debug
	return (0);
}
