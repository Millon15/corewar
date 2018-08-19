/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 18:14:56 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/19 22:00:17 by vbrazas          ###   ########.fr       */
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
	init_pair(BORDER, COLOR_CYAN, COLOR_CYAN);
	init_pair(MAIN, COLOR_WHITE, COLOR_BLACK);
	init_pair(INFO, COLOR_WHITE, COLOR_BLACK);
	init_pair(0, COLOR_GREEN, COLOR_BLACK);
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
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
	refresh();
	print_one_cycle(e, v);
}
