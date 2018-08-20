/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 18:14:56 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/20 17:49:08 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		init_visualizer(void)
{
	initscr();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(false);
	cbreak();
	noecho();
	use_default_colors();
	start_color();
	init_color(COLOR_DARK, 550, 550, 550);
	init_pair(BORDER, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(MAIN, COLOR_WHITE, COLOR_BLACK);
	init_pair(INFO, COLOR_WHITE, COLOR_BLACK);
	init_pair(P1_COLOR, COLOR_GREEN, COLOR_BLACK);
	init_pair(P2_COLOR, COLOR_BLUE, COLOR_BLACK);
	init_pair(P3_COLOR, COLOR_RED, COLOR_BLACK);
	init_pair(P4_COLOR, COLOR_CYAN, COLOR_BLACK);
}

void					init_windows(t_curses *e, t_vm *v)
{
	init_visualizer();
	e->mainw = newwin(WHEIGHT, MW_WIDTH, 0, 0);
	wattron(e->mainw, COLOR_PAIR(BORDER));
	wborder(e->mainw, BORDC, BORDC, BORDC, BORDC, BORDC, BORDC, BORDC, BORDC);
	wattroff(e->mainw, COLOR_PAIR(BORDER));
	e->infow = newwin(WHEIGHT, IW_WIDTH, 0, MW_WIDTH - 1);
	wattron(e->infow, COLOR_PAIR(BORDER));
	wborder(e->infow, BORDC, BORDC, BORDC, BORDC, BORDC, BORDC, BORDC, BORDC);
	wattroff(e->infow, COLOR_PAIR(BORDER));
	wattron(e->infow, COLOR_PAIR(INFO) | A_BOLD);
	e->t = clock();
	e->is_run = false;
	e->cycles_in_second = 50;
	refresh();
	print_one_cycle(e, v, false);
}

void					deinit_windows(t_curses *e, t_vm *v)
{
	wattroff(e->infow, COLOR_PAIR(INFO) | A_BOLD);
	delwin(e->mainw);
	delwin(e->infow);
	endwin();
	system("reset");
}
