/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cycle_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 20:29:14 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/19 19:46:11 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		kill_process(t_car *car, t_vm *v)
{
	while (car)
	{
		if (!car->nb_lives)
		{
			delete_this_car(car, v);
			continue ;
		}
		car = car->next;
	}
}

bool		nbr_live_exec(t_car *car)
{
	int cnt;

	cnt = 0;
	while (car)
	{
		if (car->nb_lives)
			cnt += car->nb_lives;
		if (cnt >= NBR_LIVE)
			return (true);
		car = car->next;
	}
	return (false);
}

void		make_live_nil(t_vm *v)
{
	int		i;
	t_car	*car;

	i = -1;
	car = v->head;
	while (car)
	{
		car->nb_lives = 0;
		car = car->next;
	}
	while (++i < v->player_amount)
		v->player[i].lives_in_cp = 0;
}
