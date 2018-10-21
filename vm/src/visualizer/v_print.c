/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 01:41:00 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/21 06:18:57 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#define CLEAR_LINE		20
#define MW_ROW_LENGTH	64
#define PRINT_WIDGET	(!(I.cur_cycle % 10))

static void				print_main(t_vm *v)
{
	int					row;
	int					i;
	int					attrs;

	i = -1;
	row = START_ROW - 1;
	put_car_color_to_arena(v);
	while (++i < MEM_SIZE)
	{
		if ((i % MW_ROW_LENGTH) == 0)
			wmove(N->mainw, ++row, 4);
		attrs = COLOR_PAIR(N->clr[i].main)
		| ((N->clr[i].bold > 0) ? A_BOLD : 0)
		| ((N->clr[i].undrln > 0) ? A_UNDERLINE | A_BOLD : 0);
		wattron(N->mainw, attrs);
		wprintw(N->mainw, "%0.2x", (A.is_stealth) ? 0xff : v->arena[i]);
		wattroff(N->mainw, attrs);
		waddch(N->mainw, ' ');
		(N->clr[i].bold > 0) ? N->clr[i].bold-- : false;
		(N->clr[i].undrln > 0) ? N->clr[i].undrln-- : false;
	}
	wrefresh(N->mainw);
}

static void				print_full_info(t_vm *v, int row, int i)
{
	while (++i < v->player_amount)
	{
		mvwprintw(N->infow, (row += 2), 4, "Player -%d : ", i + 1);
		wattron(N->infow, COLOR_PAIR(N->pcolors[i]));
		wprintw(N->infow, "%.*s", IW_WIDTH - 18, P(i).prog_name);
		wattroff(N->infow, COLOR_PAIR(N->pcolors[i]));
		mvwprintw(N->infow, ++row, 6, "Last live :\t\t\t%-*d",
		CLEAR_LINE, P(i).points);
		mvwprintw(N->infow, ++row, 6, "Lives in current period :\t\t%-*d",
		CLEAR_LINE, P(i).lives_in_cp);
	}
	(PRINT_WIDGET) ? print_widgets(v, &row) : (row += 6);
	mvwprintw(N->infow, (row += 2), 4, "CYCLE_TO_DIE :\t%-*d",
	CLEAR_LINE, I.cycle_to_die);
	mvwprintw(N->infow, (row += 2), 4, "CYCLE_DELTA :\t%-*d",
	CLEAR_LINE, CYCLE_DELTA);
	mvwprintw(N->infow, (row += 2), 4, "NBR_LIVE :\t\t%-*d",
	CLEAR_LINE, NBR_LIVE);
	mvwprintw(N->infow, (row += 2), 4, "MAX_CHECKS :\t%-*d",
	CLEAR_LINE, MAX_CHECKS);
}

void					print_info(t_vm *v, const bool is_print_full_info)
{
	int					row;
	int					i;

	row = START_ROW;
	i = -1;
	wattron(N->infow, COLOR_PAIR(COLOR_DARK));
	mvwprintw(N->infow, COMMON_HEIGHT - 4, ALIGN_CENTER(IW_WIDTH, 13),
	"%-*s", CLEAR_LINE, (N->is_run) ? "** RUNNING **" : "** PAUSED **");
	mvwprintw(N->infow, row, 4, "Cycles/second limit :\t%-*d"
	, CLEAR_LINE, N->cycpersec);
	wattroff(N->infow, COLOR_PAIR(COLOR_DARK));
	mvwprintw(N->infow, (row += 3), 4, "Cycle :\t\t%-*d",
	CLEAR_LINE, I.cur_cycle);
	mvwprintw(N->infow, (row += 2), 4, "Processes :\t\t%-*d",
	CLEAR_LINE, I.cursors);
	if (is_print_full_info)
		print_full_info(v, row, i);
	wrefresh(N->infow);
}

void					print_one_cycle(t_vm *v, const bool is_pass_cycle)
{
	print_main(v);
	print_info(v, true);
	(PRINT_WIDGET && !A.is_nostat) ? print_stats(v) : false;
	put_border(N->mainw);
	put_border(N->infow);
	put_border(N->statw);
	if (is_pass_cycle)
		pass_one_cycle(v);
}
