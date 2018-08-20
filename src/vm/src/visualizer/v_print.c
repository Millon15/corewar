/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 01:41:00 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/20 17:46:56 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void					print_main(t_curses *e, t_vm *v)
{
	int				row;
	int				i;
	unsigned char	prev_color;

	row = ROW_MAIN;
	i = 0;
	prev_color = v->color[0];
	wattron(e->mainw, COLOR_PAIR(prev_color));
	mvwprintw(e->mainw, ++row, 4, "%0.2x ", v->arena[i]);
	while (++i < MEM_SIZE)
	{
		if (prev_color != v->color[i])
		{
			wattroff(e->mainw, COLOR_PAIR(
			(prev_color == 0x0) ? MAIN : v->color[i]) | A_DIM);
			prev_color = v->color[i];
			wattron(e->mainw, COLOR_PAIR(
			(v->color[i] == 0x0) ? MAIN : v->color[i]) | A_DIM);
		}
		if (!(i % 64))
			mvwprintw(e->mainw, ++row, 4, "%0.2x ", v->arena[i]);
		else
			wprintw(e->mainw, "%0.2x ", v->arena[i]);
	}
	wattroff(e->mainw, COLOR_PAIR(prev_color));
	wrefresh(e->mainw);
}

static inline void		print_full_info(t_curses *e, t_vm *v, int row, int i)
{
	mvwprintw(e->infow, (row += 2), 4, "Cycle\t:\t%-*d",
	CL_PADD, I.cur_cycle);
	mvwprintw(e->infow, (row += 2), 4, "Processes\t:\t%-*d",
	CL_PADD, I.cursors);
	row++;
	while (++i < v->player_amount)
	{
		mvwprintw(e->infow, (row += 2), 4, "Player -%d : %s %s",
		i + 1, v->player[i].prog_name, v->player[i].comment);
		mvwprintw(e->infow, ++row, 6, "Last live\t\t\t:\t%-*d",
		CL_PADD, v->player[i].points);
		mvwprintw(e->infow, ++row, 6, "Lives in current period\t:\t%-*d",
		CL_PADD, v->player[i].lives_in_cp);
	}
	mvwprintw(e->infow, (row += 3), 4, "CYCLE_TO_DIE:\t%-*d",
	CL_PADD, I.cycle_to_die);
	mvwprintw(e->infow, (row += 2), 4, "CYCLE_DELTA\t:\t%-*d",
	CL_PADD, CYCLE_DELTA);
	mvwprintw(e->infow, (row += 2), 4, "NBR_LIVE\t:\t%-*d",
	CL_PADD, NBR_LIVE);
	mvwprintw(e->infow, (row += 2), 4, "MAX_CHECKS\t:\t%-*d",
	CL_PADD, MAX_CHECKS);
}

void					print_info(t_curses *e, t_vm *v,
	bool is_print_full_info)
{
	int			row;
	int			i;

	row = ROW_INFO;
	i = -1;
	mvwprintw(e->infow, WHEIGHT - 4, ALIGN_CENTER(IW_WIDTH, 13),
	"%-*s", CL_PADD, (e->is_run) ? "** RUNNING **" : "** PAUSED **");
	mvwprintw(e->infow, row, 4, "Cycles/second limit :\t%-*d",
	CL_PADD, e->cycles_in_second);
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
