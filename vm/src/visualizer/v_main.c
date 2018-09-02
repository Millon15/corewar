/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:56:16 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/31 16:06:06 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static bool				quicker_slower(t_curses *e, t_vm *v)
{
	if (e->c == RUN_QUICKER)
		e->cycles_per_second =
		((e->cycles_per_second + SQBIG_VAL) < SQMAX_VAL) ?
		(e->cycles_per_second + SQBIG_VAL) : SQMAX_VAL;
	else if (e->c == RUN_SLOWER)
		e->cycles_per_second = (e->cycles_per_second > SQBIG_VAL) ?
		(e->cycles_per_second - SQBIG_VAL) : 1;
	else if (e->c == RUN_QUICKER2)
		e->cycles_per_second =
		((e->cycles_per_second + SQSMALL_VAL) < SQMAX_VAL) ?
		(e->cycles_per_second + SQSMALL_VAL) : SQMAX_VAL;
	else if (e->c == RUN_SLOWER2)
		e->cycles_per_second = (e->cycles_per_second > SQSMALL_VAL) ?
		(e->cycles_per_second - SQSMALL_VAL) : 1;
	else
		return (false);
	return (true);
}

void					visualize_the_game(t_vm *v)
{
	t_curses			e;

	init_windows(&e, v);
	while ((e.c = getch()) != EXIT_KEY && I.cycle_to_die > 0)
	{
		if (e.c == RUN)
		{
			e.is_run = !e.is_run;
			print_info(&e, v, false);
		}
		else if (e.c == PASS_OVER)
			print_one_cycle(&e, v, true);
		else if (e.is_run && clock() >= CLOCK_FORMULA)
		{
			print_one_cycle(&e, v, true);
			e.t = clock();
		}
		else if (quicker_slower(&e, v))
			print_info(&e, v, false);
	}
	deinit_windows(&e, v);
}
