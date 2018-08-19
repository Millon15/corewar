/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:56:16 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/19 21:59:36 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static bool				quicker_slower(t_curses *e, t_vm *v)
{
	if (e->c == RUN_QUICKER)
	{
		e->cycles_in_second += SQBIG_VAL;
		return (true);
	}
	else if (e->c == RUN_SLOWER)
	{
		e->cycles_in_second =					\
		(e->cycles_in_second <= SQBIG_VAL) ?	\
		1 : (e->cycles_in_second - SQBIG_VAL);
		return (true);
	}
	else if (e->c == RUN_QUICKER2)
	{
		e->cycles_in_second += SQSMALL_VAL;
		return (true);
	}
	else if (e->c == RUN_SLOWER2)
	{
		e->cycles_in_second =					\
		(e->cycles_in_second <= SQSMALL_VAL) ?	\
		1 : (e->cycles_in_second - SQSMALL_VAL);
		return (true);
	}
	return (false);
}

void					visualize_the_game(t_vm *v)
{
	t_curses			e;

	init_windows(&e, v);
	while ((e.c = getch()) != EXIT_KEY)
	{
		if (e.c == RUN)
		{
			e.is_run = !e.is_run;
			mvwprintw(e.infow, WHEIGHT - 4, ALIGN_CENTER(IW_WIDTH, 13),
			"%-*s", CL_PADD, (e.is_run) ? "** RUNNING **" : "** PAUSED **");
			wrefresh(e.infow);
		}
		else if (e.c == PASS_OVER)
		{
			print_one_cycle(&e, v);
			pass_one_cycle(v);
		}
		if (e.is_run && clock() >= (e.t + CLOCKS_PER_SEC / e.cycles_in_second))
		{
			print_one_cycle(&e, v);
			pass_one_cycle(v);
			e.t = clock();
		}
		else if (quicker_slower(&e, v))
		{
			mvwprintw(e.infow, ROW_INFO, 4, "Cycles/second limit:\t%-*d",
			CL_PADD, e.cycles_in_second);
			wrefresh(e.infow);
		}
	}
	wattroff(e->mainw, COLOR_PAIR(INFO) | A_BOLD);
	endwin();
	system("reset;");
}
