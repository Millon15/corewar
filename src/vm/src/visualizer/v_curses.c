/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_curses.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 18:14:56 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/18 21:37:13 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void			init_visualizer(t_vm *v)
{
	initscr();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(false);
	clear();
	noecho();
	cbreak();
	// start_color();
	// init_color(COLOR_WHITE, 220, 220, 220);
	// init_pair(0, COLOR_YELLOW, COLOR_BLACK);
	// init_pair(1, COLOR_BLUE, COLOR_BLACK);
	// init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	// init_pair(3, COLOR_CYAN, COLOR_BLACK);
	// init_pair(4, COLOR_RED, COLOR_BLACK);
	// init_pair(5, COLOR_GREEN, COLOR_BLACK);
	// init_pair(6, COLOR_YELLOW, COLOR_BLACK);
	// init_pair(7, COLOR_BLACK, COLOR_BLUE);
	// init_pair(8, COLOR_BLACK, COLOR_MAGENTA);
	// init_pair(9, COLOR_BLACK, COLOR_CYAN);
	// init_pair(10, COLOR_BLACK, COLOR_RED);
	// init_pair(11, COLOR_BLACK, COLOR_GREEN);
	// init_pair(12, COLOR_WHITE, COLOR_BLACK);
	// init_pair(13, COLOR_BLACK, COLOR_GREEN);
	// init_pair(14, COLOR_GREEN, COLOR_BLACK);
}

void			init_windows(t_curses *e, t_vm *v)
{
	const int	size_y = 100;
	const int	size_x = 200;

	e->wmain = newwin(size_y, size_x, 0, 0);
	e->winfo = newwin(size_y, (int)(size_x / 2.5), 0, size_x);
	e->t = clock() / CLOCKS_PER_SEC;
	e->is_run = false;
	e->cycles_in_second = 50;
	print_one_cycle(e, v);
}

void			print_one_cycle(t_curses *e, t_vm *v)
{
	box(e->wmain, 0, 0);
	box(e->winfo, 0, 0);
}
