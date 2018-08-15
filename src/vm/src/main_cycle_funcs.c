/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cycle_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 20:29:14 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/15 22:19:11 by vbrazas          ###   ########.fr       */
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

void		make_live_nil(t_car *car)
{
	while (car)
	{
		car->nb_lives = 0;
		car = car->next;
	}
}
