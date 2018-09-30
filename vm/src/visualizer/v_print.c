/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 01:41:00 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/30 13:56:05 by vbrazas          ###   ########.fr       */
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
	put_car_color_to_arena(v);
	while (++i < MEM_SIZE)
	{
		if ((i % MW_ROW_LENGHT) == 0)
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

static inline void		print_full_info(t_vm *v, int row, int i)
{
	while (++i < v->player_amount)
	{
		mvwprintw(N->infow, (row += 2), 4, "Player -%d : ", i + 1);
		wattron(N->infow, COLOR_PAIR(N->pcolors[i]));
		wprintw(N->infow, "%.*s", IW_WIDTH - 18, P(i).prog_name);
		wattroff(N->infow, COLOR_PAIR(N->pcolors[i]));
		mvwprintw(N->infow, ++row, 6, "Last live :\t\t\t%-*d",
		CLEAR_LINE_PADD, P(i).points);
		mvwprintw(N->infow, ++row, 6, "Lives in current period :\t\t%-*d",
		CLEAR_LINE_PADD, P(i).lives_in_cp);
	}
	print_widgets(v, &row);
	mvwprintw(N->infow, (row += 2), 4, "CYCLE_TO_DIE :\t%-*d",
	CLEAR_LINE_PADD, I.cycle_to_die);
	mvwprintw(N->infow, (row += 2), 4, "CYCLE_DELTA :\t%-*d",
	CLEAR_LINE_PADD, CYCLE_DELTA);
	mvwprintw(N->infow, (row += 2), 4, "NBR_LIVE :\t\t%-*d",
	CLEAR_LINE_PADD, NBR_LIVE);
	mvwprintw(N->infow, (row += 2), 4, "MAX_CHECKS :\t%-*d",
	CLEAR_LINE_PADD, MAX_CHECKS);
}

inline void				print_info(t_vm *v, const bool is_print_full_info)
{
	int			row;
	int			i;

	row = START_ROW_INFO;
	i = -1;
	// wattron(N->infow, COLOR_PAIR(COLOR_BLUE));
	mvwprintw(N->infow, COMMON_HEIGHT - 4, ALIGN_CENTER(IW_WIDTH, 13),
	"%-*s", CLEAR_LINE_PADD, (N->is_run) ? "** RUNNING **" : "** PAUSED **");
	mvwprintw(N->infow, row, 4, "Cycles/second limit :\t%-*d",
	CLEAR_LINE_PADD, N->cycpersec);
	// wattroff(N->infow, COLOR_PAIR(COLOR_BLUE));
	mvwprintw(N->infow, (row += 3), 4, "Cycle :\t\t%-*d",
	CLEAR_LINE_PADD, I.cur_cycle);
	mvwprintw(N->infow, (row += 2), 4, "Processes :\t\t%-*d",
	CLEAR_LINE_PADD, I.cursors);
	if (is_print_full_info)
		print_full_info(v, row, i);
	wrefresh(N->infow);
}

static inline void		print_stats_directly(t_vm *v
	, int cur_terminator, int i, int row)
{
	static const int	strip_width = SW_WIDTH - SW_WIDTH / 8 * 2;
	int					min;
	int					max;

	min = strip_width / (cur_terminator ? cur_terminator : UINT_MAX);
	max = strip_width / (P(i).total_lives ? P(i).total_lives : UINT_MAX);
	while (++min < max)
		wprintw(N->statw, " ");
	min = strip_width / (cur_terminator ? cur_terminator : UINT_MAX);
	(P(i).total_lives > 0) ? mvwprintw(N->statw, row, min, "%d %d", min, max) : false;
	// wattron(N->statw, COLOR_PAIR(N->scolors[i]));
	// (P(i).total_lives > 0) ? mvwprintw(N->statw, row, min, " ") : false;
	// while (++min < max)
	// 	wprintw(N->statw, " ");
	// wattroff(N->statw, COLOR_PAIR(N->scolors[i]));
}

static inline void		print_stats(t_vm *v)
{
	static int			cur_terminator = TOT_LIVES_TERM;
	static const int	name_len = SW_WIDTH / 8;
	int					row;
	int					i;

	i = -1;
	while (++i < v->player_amount)
		if (P(i).total_lives + 100 >= cur_terminator)
			cur_terminator *= 2;
	i = -1;
	row = START_ROW_STAT - 1;
	while (++i < v->player_amount)
	{
		mvwprintw(N->statw, ++row, 4, "Player -%d ", i + 1);
		wattron(N->statw, COLOR_PAIR(N->pcolors[i]));
		wprintw(N->statw, "\"%*.*s\"", name_len, name_len, P(i).prog_name);
		wattroff(N->statw, COLOR_PAIR(N->pcolors[i]));
		wprintw(N->statw, " : %6d : ", P(i).total_lives);
		print_stats_directly(v, cur_terminator, i, row);
	}
	wrefresh(N->statw);
}

void					print_one_cycle(t_vm *v, const bool is_pass_cycle)
{
	print_main(v);
	print_info(v, true);
	print_stats(v);
	if (is_pass_cycle)
		pass_one_cycle(v);
}
