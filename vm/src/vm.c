/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:56:16 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/17 19:55:18 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		end_the_game(t_vm *v)
{
	get_winner(v);
	ft_printf("Contestant %d, \"%s\", has won !\n"
	, I.winner + 1, P(I.winner).prog_name);
}

static inline void		start_the_game(t_vm *v)
{
	int				i;

	i = -1;
	ft_putstr("Introducing contestants...\n");
	while (++i < v->player_amount)
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		i + 1, P(i).prog_size,
		P(i).prog_name, P(i).comment);
}

void					pass_one_cycle(t_vm *v)
{
	t_car					*cur_car;
	static unsigned int		last_check = 0;

	!(A.verbose_value & 2) ? ++I.cur_cycle :
	ft_printf("It is now cycle %d\n", ++I.cur_cycle);
	last_check++;
	cur_car = v->head;
	while (cur_car)
	{
		perform_next_comm(cur_car, v);
		cur_car = cur_car->next;
	}
	if (last_check == I.cycle_to_die || I.cycle_to_die < 0)
	{
		kill_process(&last_check, v);
		if (nbr_live_exec(v->head) || I.cycle_to_delta <= I.cur_cycle)
		{
			I.cycle_to_die -= CYCLE_DELTA;
			if (A.verbose_value & 2 && v->head)
				ft_printf("Cycle to die is now %d\n", I.cycle_to_die);
			I.cycle_to_delta = I.cur_cycle + I.cycle_to_die * MAX_CHECKS;
		}
		make_live_nil(v);
	}
}

static inline void		play_the_game(t_vm *v)
{
	I.cycle_to_die = CYCLE_TO_DIE;
	I.cycle_to_delta = CYCLE_TO_DIE * MAX_CHECKS;
	if (A.is_ncurses)
	{
		visualize_the_game(v);
		return ;
	}
	start_the_game(v);
	if (A.is_dump)
	{
		while (v->head && A.dump_value > I.cur_cycle)
			pass_one_cycle(v);
		dump_printer(v->arena, MEM_SIZE);
	}
	else
		while (v->head)
			pass_one_cycle(v);
}

int						main(int ac, char **av)
{
	t_vm		*v;

	v = (t_vm *)ft_memalloc(sizeof(t_vm));
	ft_bzero(&(v->args), sizeof(v->args));
	ft_bzero(&(v->info), sizeof(v->info));
	check_and_obtain_args(ac, av, v);
	fill_players(v);
	fill_arena(v);
	play_the_game(v);
	end_the_game(v);
	return (0);
}
