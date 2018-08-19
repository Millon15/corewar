/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 01:41:00 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/19 19:52:59 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		print_main(t_curses *e, t_vm *v, int row, int i)
{
	mvwprintw(e->mainw, ++row, 4, "%0.2x ", v->arena[i]);
	while (++i < MEM_SIZE)
	{
		if (!(i % 64))
			mvwprintw(e->mainw, ++row, 4, "%0.2x ", v->arena[i]);
		else
			wprintw(e->mainw, "%0.2x ", v->arena[i]);
	}
	wrefresh(e->mainw);
}

static inline void		print_info(t_curses *e, t_vm *v, int row, int i)
{
	mvwprintw(e->infow, WHEIGHT - 4, ALIGN_CENTER(IW_WIDTH, 13), "%s",
	(e->is_run) ? "** RUNNING **" : "** PAUSED **");
	mvwprintw(e->infow, row, 4, "Cycles/second limit : %-*d",
	CL_PADD, e->cycles_in_second);
	mvwprintw(e->infow, (row += 2), 4, "Cycle :\t\t%-*d",
	CL_PADD, I.cur_cycle);
	mvwprintw(e->infow, (row += 1), 4, "Processes :\t\t%-*d",
	CL_PADD, I.cursors);
	while (++i < v->player_amount)
	{
		mvwprintw(e->infow, (row += 2), 4, "Player -%d : %s %s",
		i + 1, v->player[i].prog_name, v->player[i].comment);
		mvwprintw(e->infow, ++row, 6, "Last live :\t\t\t%-*d",
		CL_PADD, v->player[i].points);
		mvwprintw(e->infow, ++row, 6, "Lives in current period :\t\t%-*d",
		CL_PADD, v->player[i].lives_in_cp);
	}
	mvwprintw(e->infow, (row += 2), 4, "CYCLE_TO_DIE :\t%-*d",
	CL_PADD, I.cycle_to_die);
	mvwprintw(e->infow, (row += 1), 4, "CYCLE_DELTA :\t%-*d",
	CL_PADD, CYCLE_DELTA);
	mvwprintw(e->infow, (row += 1), 4, "NBR_LIVE :\t%-*d",
	CL_PADD, NBR_LIVE);
	mvwprintw(e->infow, (row += 1), 4, "MAX_CHECKS :\t%-*d",
	CL_PADD, MAX_CHECKS);
	wrefresh(e->infow);
}

void					print_one_cycle(t_curses *e, t_vm *v)
{
	print_main(e, v, 1, 0);
	print_info(e, v, 2, -1);
	pass_one_cycle(v);
}
