/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:56:16 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/14 18:47:53 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void					print_pc(unsigned char *pc)
{
	int i;

	i = 0;
	while (i < 10)
	{
		ft_printf("%0.2x ", pc[i]);
		i++;
	}
	ft_putchar('\n');
}

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
			// ft_printf("who: %d | pc: %p | %0.2x\n", cur_car->whom, cur_car->pc, *cur_car->pc);
			// print_pc(cur_car->pc);
			cur_car->perform_next_comm(cur_car, v);
			cur_car = cur_car->next;
		}
		// if ()
			cycle_to_die -= CYCLE_DELTA;
	}
}

void					print_carriage(t_car *car)
{
	while (car)
	{
		ft_printf("whom: %d | pc: %0.2x\n", car->whom, car->pc[0]);
		car = car->next;
	}
}

int						main(int ac, char **av)
{
	t_vm		v;

	ft_bzero(&v, sizeof(v));
	check_and_obtain_args(ac, av, &v);
	fill_players(&v);
	fill_arena(&v);
	// print_carriage((&v)->head);
	// print_arena_to_stdout(&v); // debug
	do_all_stuff(&v);
	return (0);
}
