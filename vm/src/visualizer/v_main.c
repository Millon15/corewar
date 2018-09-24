/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyltsov <apyltsov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 21:53:27 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/24 16:19:51 by apyltsov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static bool				quicker_slower(t_vm *v)
{
	if (N->c == RUN_QUICKER)
		N->cycpersec += SQBIG_VAL;
	else if (N->c == RUN_SLOWER)
		N->cycpersec -= SQBIG_VAL;
	else if (N->c == RUN_QUICKER2)
		N->cycpersec += SQSMALL_VAL;
	else if (N->c == RUN_SLOWER2)
		N->cycpersec -= SQSMALL_VAL;
	else
		return (false);
	if (N->cycpersec < 1)
		N->cycpersec = 1;
	else if (N->cycpersec > SQMAX_VAL)
		N->cycpersec = SQMAX_VAL;
	return (true);
}

#define CLOCK_FORMULA	(N->t + CLOCKS_PER_SEC / N->cycpersec)

void					visualize_the_game(t_vm *v)
{
	init_windows(v);
	while ((N->c = getch()) != EXIT_KEY && v->head)
	{
		if (N->c == RUN)
		{
			N->is_run = !N->is_run;
			print_info(v, false);
		}
		else if (N->c == PASS_OVER)
			print_one_cycle(v, true);
		else if (N->is_run && clock() >= CLOCK_FORMULA)
		{
			N->t = clock();
			print_one_cycle(v, true);
		}
		else if (quicker_slower(v))
			print_info(v, false);
	}
	deinit_windows(v);
}
