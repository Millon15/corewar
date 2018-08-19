/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:56:16 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/19 21:01:07 by akupriia         ###   ########.fr       */
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
		(e->cycles_in_second - SQBIG_VAL) : 1;
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
		(e->cycles_in_second - SQSMALL_VAL) : 1;
		return (true);
	}
	return (false);
}

void					visualize_the_game(t_vm *v)
{
	t_curses			e;
	int row = 50;

	init_windows(&e, v);
	while ((e.c = getch()) != EXIT_KEY)
	{
		if (e.c == RUN)
		{
			// mvwprintw(e.infow, row++, 4, "%d", e.t); wrefresh(e.infow);
			e.is_run = !e.is_run;
		}
		else if (e.c == PASS_OVER)
			print_one_cycle(&e, v);
		if (e.is_run && e.t != (clock() / CLOCKS_PER_SEC / e.cycles_in_second))
		{
			// mvwprintw(e.infow, row++, 4, "2"); wrefresh(e.infow);
			print_one_cycle(&e, v);
			e.t = clock() / CLOCKS_PER_SEC;
		}
		// else if (quicker_slower(&e, v))
		// 	continue ;
	}
	endwin();
	system("clear; reset;");
}
