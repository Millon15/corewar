/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 18:14:56 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/23 02:48:02 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		init_colors(t_curses *e, t_vm *v)
{
	int				i;
	unsigned char	*from;
	unsigned char	*to;
	t_car			*cur_pl_car;

	e->acolor = ft_memalloc(sizeof(unsigned char) * MEM_SIZE);
	e->pcolor = ft_memalloc(sizeof(short) * MAX_PLAYERS);
	e->ccolor = ft_memalloc(sizeof(short) * MAX_PLAYERS);
	i = -1;
	while (++i < MAX_PLAYERS)
		e->pcolor[i] = PCOLORS + i;//COLOR_PAIR(PCOLORS + i); // Why we cannot do it???
	i = -1;
	while (++i < MAX_PLAYERS)
		e->ccolor[i] = CCOLORS + i;//COLOR_PAIR(CCOLORS + i); // Why we cannot do it???
	i = -1;
	cur_pl_car = v->head;
	while (cur_pl_car && ++i < v->player_amount)
	{
		from = e->acolor + (cur_pl_car->pc - v->arena);
		to = from + P(i).prog_size;
		*from = e->ccolor[i];
		while (++from < to)
			*from = e->pcolor[i];
		cur_pl_car = cur_pl_car->next;
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

void					init_windows(t_curses *e, t_vm *v)
{
	// fd = open("log", O_WRONLY | O_TRUNC | O_CREAT, 0644); // debug

	init_visualizer();
	init_colors(e, v);
	e->mainw = newwin(COMMON_HEIGHT, START_MW_WIDTH, 0, 0);
	wattron(e->mainw, COLOR_PAIR(BORDER));
	wborder(e->mainw, BORDC, BORDC, BORDC, BORDC, BORDC, BORDC, BORDC, BORDC);
	wattroff(e->mainw, COLOR_PAIR(BORDER));
	e->infow = newwin(COMMON_HEIGHT, START_IW_WIDTH, 0, START_MW_WIDTH - 1);
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

	// for (int k = 0; k < 4; k++)
	// 	ft_dprintf(fd, "PCOLOR_%d : %d\nCCOLOR_%d : %d\n", k, e->pcolor[k], k, e->ccolor[k]);
	// ft_dprintf(fd, "ACOLOR:\n%3d ", e->acolor[0]);
	// for (int i = 1; i < MEM_SIZE; i++)
	// {
	// 	if (!(i % 64))
	// 		ft_dprintf(fd, "%3d\n", e->acolor[i]);
	// 	else
	// 		ft_dprintf(fd, "%3d ", e->acolor[i]);
	// }
	// ft_dprintf(fd, "\n");

	free(e->acolor);
	free(e->pcolor);
	free(e->ccolor);
	system("reset");

	// system("cat log"); // debug
}
