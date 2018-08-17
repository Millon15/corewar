/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuzlizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:56:16 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/17 05:29:31 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

#define I				v->info

static inline void		init_visualizer(t_vm *v)
{
	initscr();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(false);
	clear();
	noecho();
	cbreak();
	start_color();
	init_color(COLOR_WHITE, 220, 220, 220);
	init_pair(0, COLOR_YELLOW, COLOR_BLACK);
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);
	init_pair(7, COLOR_BLACK, COLOR_BLUE);
	init_pair(8, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(9, COLOR_BLACK, COLOR_CYAN);
	init_pair(10, COLOR_BLACK, COLOR_RED);
	init_pair(11, COLOR_BLACK, COLOR_GREEN);
	init_pair(12, COLOR_WHITE, COLOR_BLACK);
	init_pair(13, COLOR_BLACK, COLOR_GREEN);
	init_pair(14, COLOR_GREEN, COLOR_BLACK);
}

static inline void		pass_one_cycle(t_curses *e, t_vm *v)
{
	box(e->wmain, 0, 0);
	box(e->winfo, 0, 0);
}

static inline void		init_windows(t_curses *e, t_vm *v)
{
	const int	size_y = 100;
	const int	size_x = 200;

	e->wmain = newwin(size_y, size_x, 0, 0);
	e->winfo = newwin(size_y, (int)(size_x / 2.5), 0, size_x);
	e->t = clock();
	e->is_run = false;
	e->cycles_in_second = 50;
	pass_one_cycle(e, v);
}

static bool		quicker_slower(t_curses *e, t_vm *v)
{
	if (e->c == RUN_QUICKER)
	{
		e->cycles_in_second += SQBIG_VAL;
		return (true);
	}
	else if (e->c == RUN_SLOWER)
	{
		e->cycles_in_second =
		(e->cycles_in_second <= SQBIG_VAL) ?
		(e->cycles_in_second - SQBIG_VAL) : 1;
		return (true);
	}
	else if (e->c == RUN_QUICKER2)
	{
		e->cycles_in_second += SQSMALL_VAL;
		return (true);
	}
	else if (e->c == RUN_SLOWER2)
	{
		e->cycles_in_second =
		(e->cycles_in_second <= SQSMALL_VAL) ?
		(e->cycles_in_second - SQSMALL_VAL) : 1;
		return (true);
	}
	return (false);
}

static inline void		quicker_slower(t_curses *e, t_vm *v)
{
	while (e->is_run)
	{
		if (e->t != (clock() + CLOCKS_PER_SEC / e->cycles_in_second))
		{
			pass_one_cycle(&e, v);
			e->t = clock();
		}
		e->c = getch();
		if (e->c == RUN)
		{
			e->is_run = false;
			return ;
		}
	}
}

void					visualize_the_game(t_vm *v)
{
	t_curses			e;

	init_windows(&e, v);
	while (true)
	{
		pass_cycles_while_run(&e, v);
		e.c = getch();
		if (e.c == RUN)
			e.is_run = true;
		else if (e.c == PASS_OVER)
			pass_one_cycle(&e, v);
		else if (quicker_slower(&e, v))
			continue ;
		else if (e.c == EXIT_KEY)
			break ;
	}
}
