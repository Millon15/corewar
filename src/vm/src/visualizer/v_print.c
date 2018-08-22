/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 01:41:00 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/23 02:18:25 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		update_colors(t_curses *e, t_vm *v)
{
	int				i;
	unsigned char	*from;
	unsigned char	*to;
	t_car			*cur_pl_car;

	i = -1;
	while (++i < MAX_PLAYERS)
		e->pcolor[i] = PCOLORS + i;//COLOR_PAIR(PCOLORS + i);
	i = -1;
	while (++i < MAX_PLAYERS)
		e->ccolor[i] = CCOLORS + i;//COLOR_PAIR(CCOLORS + i);
	i = -1;
	cur_pl_car = v->head;
	while (cur_pl_car && ++i < v->player_amount)
	{
		from = e->acolor + (cur_pl_car->pc - v->arena);
		to = e->acolor + v->player[i].prog_size;
		*from = e->ccolor[i];
		while (++from < to)
			*from = e->pcolor[i];
		cur_pl_car = cur_pl_car->next;
	}
}

static inline void		print_main(t_curses *e, t_vm *v)
{
	int				row;
	int				i;
	t_car			*car;

	row = START_ROW_MAIN - 1;
	i = -1;
	update_colors(e, v);
	while (++i < MEM_SIZE)
	{
		wattron(e->mainw, COLOR_PAIR(e->acolor[i]));
		if (!(i % 64))
			mvwprintw(e->mainw, ++row, 4, "%0.2x", v->arena[i]);
		else
			wprintw(e->mainw, "%0.2x", v->arena[i]);
		wattroff(e->mainw, COLOR_PAIR(e->acolor[i]));
		wprintw(e->mainw, " ");
	}
	wrefresh(e->mainw);
}

static inline void		print_full_info(t_curses *e, t_vm *v, int row, int i)
{
	mvwprintw(e->infow, (row += 2), 4, "Cycle\t:\t%-*d",
	CLEAR_LINE_PADD, I.cur_cycle);
	mvwprintw(e->infow, (row += 2), 4, "Processes\t:\t%-*d",
	CLEAR_LINE_PADD, I.cursors);
	row++;
	while (++i < v->player_amount)
	{
		mvwprintw(e->infow, (row += 2), 4, "Player -%d : %s %s",
		i + 1, v->player[i].prog_name, v->player[i].comment);
		mvwprintw(e->infow, ++row, 6, "Last live\t\t\t:\t%-*d",
		CLEAR_LINE_PADD, v->player[i].points);
		mvwprintw(e->infow, ++row, 6, "Lives in current period\t:\t%-*d",
		CLEAR_LINE_PADD, v->player[i].lives_in_cp);
	}
	mvwprintw(e->infow, (row += 3), 4, "CYCLE_TO_DIE:\t%-*d",
	CLEAR_LINE_PADD, I.cycle_to_die);
	mvwprintw(e->infow, (row += 2), 4, "CYCLE_DELTA\t:\t%-*d",
	CLEAR_LINE_PADD, CYCLE_DELTA);
	mvwprintw(e->infow, (row += 2), 4, "NBR_LIVE\t:\t%-*d",
	CLEAR_LINE_PADD, NBR_LIVE);
	mvwprintw(e->infow, (row += 2), 4, "MAX_CHECKS\t:\t%-*d",
	CLEAR_LINE_PADD, MAX_CHECKS);
}

void					print_info(t_curses *e, t_vm *v,
	bool is_print_full_info)
{
	int			row;
	int			i;

	row = START_ROW_INFO;
	i = -1;
	mvwprintw(e->infow, COMMON_HEIGHT - 4, ALIGN_CENTER(START_IW_WIDTH, 13),
	"%-*s", CLEAR_LINE_PADD, (e->is_run) ? "** RUNNING **" : "** PAUSED **");
	mvwprintw(e->infow, row, 4, "Cycles/second limit :\t%-*d",
	CLEAR_LINE_PADD, e->cycles_in_second);
	if (is_print_full_info)
		print_full_info(e, v, row, i);
	wrefresh(e->infow);
}

void					print_one_cycle(t_curses *e, t_vm *v, bool is_pass_cycle)
{
	print_main(e, v);
	print_info(e, v, true);
	if (is_pass_cycle)
		pass_one_cycle(v);
}
