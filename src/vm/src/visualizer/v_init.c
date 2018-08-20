/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 18:14:56 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/20 09:17:37 by vbrazas          ###   ########.fr       */
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
	// init_color(COLOR_SILVER, 240, 240, 240);
	init_pair(BORDER, COLOR_CYAN, COLOR_CYAN);
	init_pair(MAIN, COLOR_DARK, COLOR_BLACK);
	init_pair(INFO, COLOR_WHITE, COLOR_BLACK);
	init_pair(P1, COLOR_GREEN, COLOR_BLACK);
	init_pair(P2, COLOR_BLUE, COLOR_BLACK);
	init_pair(P3, COLOR_RED, COLOR_BLACK);
	init_pair(P4, COLOR_CYAN, COLOR_BLACK);
}

void					init_windows(t_curses *e, t_vm *v)
{
	init_visualizer();
	e->mainw = newwin(WHEIGHT, MW_WIDTH, 0, 0);
	e->infow = newwin(WHEIGHT, IW_WIDTH, 0, MW_WIDTH - 1);
	wattron(e->mainw, COLOR_PAIR(BORDER));
	wattron(e->infow, COLOR_PAIR(BORDER));
	wborder(e->mainw, BORDC, BORDC, BORDC, BORDC, BORDC, BORDC, BORDC, BORDC);
	wborder(e->infow, BORDC, BORDC, BORDC, BORDC, BORDC, BORDC, BORDC, BORDC);
	wattroff(e->mainw, COLOR_PAIR(BORDER));
	wattroff(e->infow, COLOR_PAIR(BORDER));
	e->t = clock();
	e->is_run = false;
	e->cycles_in_second = 50;
	wattron(e->infow, COLOR_PAIR(INFO) | A_BOLD);
	wattron(e->mainw, COLOR_PAIR(MAIN) | A_DIM);
	refresh();
	print_one_cycle(e, v, false);
}

void					deinit_windows(t_curses *e, t_vm *v)
{
	wattroff(e->infow, COLOR_PAIR(INFO) | A_BOLD);
	wattroff(e->mainw, COLOR_PAIR(MAIN) | A_DIM);
	delwin(e->mainw);
	delwin(e->infow);
	clear();
	refresh();
	endwin();
	system("clear; reset;");
}
