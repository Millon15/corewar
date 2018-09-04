/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:56:16 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/04 18:39:21 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void					end_the_game(t_vm *v)
{
	int		i;
	int		ind;

	ind = 0;
	i = -1;
	while (++i < v->player_amount)
		if (P(i).points > P(ind).points)
			ind = i;
	ft_printf("Contestant %d, \"%s\", has won !\n", ind + 1, P(ind).prog_name);
	exit(0);
}

void					pass_one_cycle(t_vm *v)
{
	int		cycle;
	// int		fl;

	// fl = false;
	cycle = I.cycle_to_die;
	I.cur_car = v->head;
	while (I.cur_car)
	{
		perform_next_comm(I.cur_car, v);
		I.cur_car = I.cur_car->next;
	}
	if ((nbr_live_exec(v->head)) ||
	(MAX_CHECKS * cycle <= I.cur_cycle))
	{
		// if (fl == true)
		// 	end_the_game(v);
		I.cycle_to_die -= CYCLE_DELTA;
		cycle += I.cycle_to_die;
		make_live_nil(v);
	}
	// if (I.cycle_to_die <= CYCLE_DELTA)
	// 	fl = true;
	I.cur_cycle++;
}

static inline void		play_the_game(t_vm *v)
{
	I.cycle_to_die = CYCLE_TO_DIE;
	if (v->args.is_ncurses)
		visualize_the_game(v);
	else
	{
		print_arena(v);
		while (I.cycle_to_die > 0)
		{
			if (v->args.is_dump && v->args.dump_value == I.cur_cycle)
				meta_printer(v->arena, MEM_SIZE);
			pass_one_cycle(v);
		}
	}
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
