/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyltsov <apyltsov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 01:41:00 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/17 22:52:27 by apyltsov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		print_main(t_vm *v)
{
	int					row;
	int					i;
	int					attrs;

	i = -1;
	row = START_ROW_MAIN - 1;
	while (++i < MEM_SIZE)
	{
		if ((i % MW_ROW_LENGHT) == 0)
			wmove(v->e->mainw, ++row, 4);
		attrs = COLOR_PAIR(v->e->acolor[i])
		| ((v->e->cbold[i] > 0) ? A_BOLD : 0)
		| ((v->e->cbold[i] > 50) ? A_UNDERLINE : 0);
		wattron(v->e->mainw, attrs);
		wprintw(v->e->mainw, "%0.2x", (A.is_stealth) ? 0xff : v->arena[i]);
		wattroff(v->e->mainw, attrs);
		waddch(v->e->mainw, ' ');
		(v->e->cbold[i] == 50 && v->arena[i] == 1) ? (v->e->cbold[i] = 0) : 0;
		(v->e->cbold[i] > 0) ? v->e->cbold[i]-- : false;
	}
	wattroff(v->e->mainw, attrs);
	wrefresh(v->e->mainw);
}

static inline void		print_full_info(t_vm *v, int row, int i)
{
	while (++i < v->player_amount)
	{
		mvwprintw(v->e->infow, (row += 2), 4, "Player -%d :", i + 1);
		wattroff(v->e->infow, COLOR_PAIR(INFO) | A_BOLD);
		wattron(v->e->infow, COLOR_PAIR(v->e->pcolors[i]) | A_BOLD);
		mvwprintw(v->e->infow, row, CLEAR_LINE_PADD, "%s", P(i).prog_name);
		wattroff(v->e->infow, COLOR_PAIR(v->e->pcolors[i]) | A_BOLD);
		wattron(v->e->infow, COLOR_PAIR(INFO) | A_BOLD);
		mvwprintw(v->e->infow, ++row, 6, "Last live\t\t\t:\t%-*d",
		CLEAR_LINE_PADD, P(i).points);
		mvwprintw(v->e->infow, ++row, 6, "Lives in current period\t:\t%-*d",
		CLEAR_LINE_PADD, P(i).lives_in_cp);
	}
	print_widgets(v, &row);
	mvwprintw(v->e->infow, (row += 2), 4, "CYCLE_TO_DIE:\t%-*d",
	CLEAR_LINE_PADD, I.cycle_to_die);
	mvwprintw(v->e->infow, (row += 2), 4, "CYCLE_DELTA\t:\t%-*d",
	CLEAR_LINE_PADD, CYCLE_DELTA);
	mvwprintw(v->e->infow, (row += 2), 4, "NBR_LIVE\t:\t%-*d",
	CLEAR_LINE_PADD, NBR_LIVE);
	mvwprintw(v->e->infow, (row += 2), 4, "MAX_CHECKS\t:\t%-*d",
	CLEAR_LINE_PADD, MAX_CHECKS);
}

void					print_info(t_vm *v)
{
	int			row;
	int			i;

	row = START_ROW_INFO;
	i = -1;
	mvwprintw(v->e->infow, COMMON_HEIGHT - 4, ALIGN_CENTER(START_IW_WIDTH, 13),
	"%-*s", CLEAR_LINE_PADD, (v->e->is_run) ? "** RUNNING **" : "** PAUSED **");
	mvwprintw(v->e->infow, row, 4, "Cycles/second limit :\t%-*d",
	CLEAR_LINE_PADD, v->e->cycles_per_second);
	mvwprintw(v->e->infow, (row += 3), 4, "Cycle\t:\t%-*d",
	CLEAR_LINE_PADD, I.cur_cycle);
	mvwprintw(v->e->infow, (row += 2), 4, "Processes\t:\t%-*d",
	CLEAR_LINE_PADD, I.cursors);
	print_full_info(v, row, i);
	wrefresh(v->e->infow);
}

void					print_one_cycle(t_vm *v, bool is_pass_cycle)
{
	print_main(v);
	print_info(v);
	if (is_pass_cycle)
		pass_one_cycle(v);
}
