/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 18:14:56 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/05 23:18:25 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		init_colors(t_vm *v)
{
	int				i;
	unsigned char	*from;
	unsigned char	*to;
	t_car			*car;

	v->e->acolor = ft_memalloc(sizeof(v->e->acolor) * MEM_SIZE);
	v->e->cbold = ft_memalloc(sizeof(v->e->cbold) * MEM_SIZE);
	i = -1;
	car = v->head;
	while (car && ++i < v->player_amount)
	{
		from = v->e->acolor + (car->pc - v->arena);
		to = from + P(i).prog_size;
		*from = CCOLORS + i;
		while (++from < to)
			*from = PCOLORS + i;
		car = car->next;
	}
}

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
	PCOLORS = P1_COLOR;
	init_pair(PCOLORS + 0, COLOR_GREEN, COLOR_BLACK);
	init_pair(PCOLORS + 1, COLOR_BLUE, COLOR_BLACK);
	init_pair(PCOLORS + 2, COLOR_RED, COLOR_BLACK);
	init_pair(PCOLORS + 3, COLOR_CYAN, COLOR_BLACK);
	CCOLORS = C1_COLOR;
	init_pair(CCOLORS + 0, COLOR_BLACK, COLOR_GREEN);
	init_pair(CCOLORS + 1, COLOR_BLACK, COLOR_BLUE);
	init_pair(CCOLORS + 2, COLOR_BLACK, COLOR_RED);
	init_pair(CCOLORS + 3, COLOR_BLACK, COLOR_CYAN);
}

void					init_windows(t_vm *v)
{
	v->e = ft_memalloc(sizeof(v->e));
	init_visualizer();
	init_colors(v);
	v->e->mainw = newwin(COMMON_HEIGHT, START_MW_WIDTH, 0, 0);
	wattron(v->e->mainw, COLOR_PAIR(BORDER));
	wborder(v->e->mainw, BORDC, BORDC, BORDC, BORDC, BORDC, BORDC, BORDC, BORDC);
	wattroff(v->e->mainw, COLOR_PAIR(BORDER));
	v->e->infow = newwin(COMMON_HEIGHT, START_IW_WIDTH, 0, START_MW_WIDTH - 1);
	wattron(v->e->infow, COLOR_PAIR(BORDER));
	wborder(v->e->infow, BORDC, BORDC, BORDC, BORDC, BORDC, BORDC, BORDC, BORDC);
	wattroff(v->e->infow, COLOR_PAIR(BORDER));
	wattron(v->e->infow, COLOR_PAIR(INFO) | A_BOLD);
	v->e->t = clock();
	v->e->is_run = true;
	v->e->cycles_per_second = 1000;
	// v->e->is_run = false;
	// v->e->cycles_per_second = START_CYCLES_PER_SEC;
	refresh();
	print_one_cycle(v, false);
}

void					deinit_windows(t_vm *v)
{
	wattroff(v->e->infow, COLOR_PAIR(INFO) | A_BOLD);
	delwin(v->e->mainw);
	delwin(v->e->infow);
	endwin();
	free(v->e->acolor);
	system("reset");
	exit(0);
}
