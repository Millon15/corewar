/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cycle_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 20:29:14 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/11 07:36:50 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		kill_process(unsigned int *last_check, t_vm *v)
{
	t_car	*car;

	car = v->head;
	while (car)
	{
		if (!car->nb_lives)
		{
			if (v->args.verbose_value & 8)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n"
				, car->id, I.cur_cycle - car->live_cycle, I.cycle_to_die);
			delete_this_car(&car, v);
			continue ;
		}
		// else if (!car->nb_lives)
		// {
		// 	car->is_alive = false;
		// 	car->death_cycle = I.cur_cycle;
		// }
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
		v->player[i].lives_in_cp = 0;
}
