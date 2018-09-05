/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 01:41:00 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/05 23:24:28 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		print_main(t_vm *v)
{
	int					row;
	int					i;

	i = -1;
	row = START_ROW_MAIN - 1;
	while (++i < MEM_SIZE)
	{
		wattron(v->e->mainw, COLOR_PAIR(v->e->acolor[i])
		| ((v->e->cbold[i]) ? A_BOLD : 0));
		if (!(i % MW_ROW_LENGHT))
			mvwprintw(v->e->mainw, ++row, 4, "%0.2x", v->arena[i]);
		else
			wprintw(v->e->mainw, "%0.2x", v->arena[i]);
		wattroff(v->e->mainw, COLOR_PAIR(v->e->acolor[i])
		| ((v->e->cbold[i]) ? A_BOLD : 0));
		wprintw(v->e->mainw, " ");
	}
	wrefresh(v->e->mainw);
}

static inline void		print_full_info(t_vm *v, int row, int i)
{
	while (++i < v->player_amount)
	{
		mvwprintw(v->e->infow, (row += 2), 4, "Player -%d :", i + 1);
		wattroff(v->e->infow, COLOR_PAIR(INFO) | A_BOLD);
		wattron(v->e->infow, COLOR_PAIR(PCOLORS + i) | A_BOLD);
		mvwprintw(v->e->infow, row, CLEAR_LINE_PADD, "%s %s",
		P(i).prog_name, "");//P(i).comment);
		wattroff(v->e->infow, COLOR_PAIR(PCOLORS + i) | A_BOLD);
		wattron(v->e->infow, COLOR_PAIR(INFO) | A_BOLD);
		mvwprintw(v->e->infow, ++row, 6, "Last live\t\t\t:\t%-*d",
		CLEAR_LINE_PADD, P(i).points);
		mvwprintw(v->e->infow, ++row, 6, "Lives in current period\t:\t%-*d",
		CLEAR_LINE_PADD, P(i).lives_in_cp);
	}
	mvwprintw(v->e->infow, (row += 3), 4, "CYCLE_TO_DIE:\t%-*d",
	CLEAR_LINE_PADD, I.cycle_to_die);
	mvwprintw(v->e->infow, (row += 2), 4, "CYCLE_DELTA\t:\t%-*d",
	CLEAR_LINE_PADD, CYCLE_DELTA);
	mvwprintw(v->e->infow, (row += 2), 4, "NBR_LIVE\t:\t%-*d",
	CLEAR_LINE_PADD, NBR_LIVE);
	mvwprintw(v->e->infow, (row += 2), 4, "MAX_CHECKS\t:\t%-*d",
	CLEAR_LINE_PADD, MAX_CHECKS);
}

void					print_info(t_vm *v,
	bool is_print_full_info)
{
	int			row;
	int			i;

	row = START_ROW_INFO;
	i = -1;
	mvwprintw(v->e->infow, COMMON_HEIGHT - 4, ALIGN_CENTER(START_IW_WIDTH, 13),
	"%-*s", CLEAR_LINE_PADD, (v->e->is_run) ? "** RUNNING **" : "** PAUSED **");
	mvwprintw(v->e->infow, row, 4, "Cycles/second limit :\t%-*d",
	CLEAR_LINE_PADD, v->e->cycles_per_second);
	mvwprintw(v->e->infow, (row += 2), 4, "Cycle\t:\t%-*d",
	CLEAR_LINE_PADD, I.cur_cycle);
	mvwprintw(v->e->infow, (row += 2), 4, "Processes\t:\t%-*d",
	CLEAR_LINE_PADD, I.cursors);
	row++;
	if (is_print_full_info)
		print_full_info(v, row, i);
	wrefresh(v->e->infow);
}

void					print_one_cycle(t_vm *v, bool is_pass_cycle)
{
	print_main(v);
	print_info(v, true);
	if (is_pass_cycle)
		pass_one_cycle(v);
}
