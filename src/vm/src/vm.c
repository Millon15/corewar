/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:56:16 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/31 15:27:19 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void					end_the_game(t_vm *v)
{
	exit(0);
}

void					pass_one_cycle(t_vm *v)
{
	if (v->args.is_dump && v->args.dump_value == I.cur_cycle)
		print_arena(v);
	I.cur_car = v->head;
	while (I.cur_car)
	{
		perform_next_comm(I.cur_car, v);
		I.cur_car = I.cur_car->next;
	}
	if ((nbr_live_exec(v->head)) ||
	(MAX_CHECKS * I.cycle_to_die <= I.cur_cycle))
	{
		// ft_printf("NB_LIVES(when I.cycle_to_die -= CYCLE_DELTA) : %d\n", v->head->nb_lives);
		I.cycle_to_die -= CYCLE_DELTA;
		make_live_nil(v);
	}
	I.cur_cycle++;
}

static inline void		play_the_game(t_vm *v)
{
	I.cycle_to_die = CYCLE_TO_DIE;
	if (v->args.is_ncurses)
		visualize_the_game(v);
	else
		while (I.cycle_to_die > 0)
			pass_one_cycle(v);
}

int						main(int ac, char **av)
{
	t_vm		v;

	ft_bzero(&v, sizeof(v));
	check_and_obtain_args(ac, av, &v);
	fill_players(&v);
	fill_arena(&v);
	play_the_game(&v);
	end_the_game(&v);
	return (0);
}
