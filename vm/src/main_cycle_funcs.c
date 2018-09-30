/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cycle_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 20:29:14 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/30 11:28:59 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		kill_process(unsigned int *last_check, t_vm *v)
{
	t_car	*car;

	car = v->head;
	while (car)
	{
		if (/*!car->nb_lives || */
		I.cur_cycle - car->live_cycle >= I.cycle_to_die || I.cycle_to_die < 0)
		{
			if (A.verbose_value & 8)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n"
				, car->id, I.cur_cycle - car->live_cycle, I.cycle_to_die);
			delete_this_car(&car, v);
			continue ;
		}
		car = car->next;
	}
	*last_check = 0;
}

bool		nbr_live_exec(t_car *car)
{
	int cnt;

	cnt = 0;
	while (car)
	{
		cnt += car->nb_lives;
		car = car->next;
	}
	return (cnt >= NBR_LIVE);
}

void		make_live_nil(t_vm *v)
{
	int		i;
	t_car	*car;

	car = v->head;
	while (car)
	{
		car->nb_lives = 0;
		car = car->next;
	}
	i = -1;
	while (++i < v->player_amount)
	{
		P(i).total_lives += P(i).lives_in_cp;
		P(i).lives_in_cp = 0;
	}
}

void		get_winner(t_vm *v)
{
	int		i;

	i = -1;
	I.winner = 0;
	while (++i < v->player_amount)
	{
		if (P(i).points > P(I.winner).points)
			I.winner = i;
		else if (P(i).points == P(I.winner).points && i != I.winner)
			if (P(i).total_lives < P(I.winner).total_lives)
				I.winner = i;
	}
}
