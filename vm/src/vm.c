/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:56:16 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/05 22:32:09 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		end_the_game(t_vm *v)
{
	int		i;
	int		ind;

	ind = 0;
	i = -1;
	while (++i < v->player_amount)
	{
		if (P(i).points > P(ind).points)
			ind = i;
		close(P(i).fd);
	}
	ft_printf("Contestant %d, \"%s\", has won !\n", ind + 1, P(ind).prog_name);
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

void					check_if_alive(t_vm *v)
{
	t_car	*car;

	car = v->head;
	while (car)
	{
		if (!car->nb_lives)
		{
			car->is_alive = false;
			car->death_cycle = I.cur_cycle;
			ft_printf("\n");
		}
		car = car->next;
	}
}

void					pass_one_cycle(t_vm *v)
{
	t_car					*cur_car;
	static unsigned int		last_check = 0;

	!(v->args.verbose_value & 2) ? ++I.cur_cycle :
	ft_printf("It is now cycle %d\n", ++I.cur_cycle);
	cur_car = v->head;
	last_check++;
	while (cur_car)
	{
		perform_next_comm(cur_car, v);
		cur_car = cur_car->next;
	}
	if (last_check == I.cycle_to_die)
	{
		kill_process(&last_check, v);
		check_if_alive(v);
		if (nbr_live_exec(v->head) || I.cycle <= I.cur_cycle)
		{
			I.cycle_to_die -= CYCLE_DELTA;
			if (v->args.verbose_value & 2)
				ft_printf("Cycle to die is now %d\n", I.cycle_to_die);
			I.cycle += I.cycle_to_die * MAX_CHECKS;
			make_live_nil(v);
		}
	}
}

static inline void		play_the_game(t_vm *v)
{
	I.cycle_to_die = CYCLE_TO_DIE;
	I.cycle = CYCLE_TO_DIE * MAX_CHECKS;
	if (v->args.is_ncurses)
		visualize_the_game(v);
	start_the_game(v);
	if (v->args.is_dump)
	{
		while (I.cycle_to_die > 0 && v->args.dump_value == I.cur_cycle)
			pass_one_cycle(v);
		dump_printer(v->arena, MEM_SIZE);
	}
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
