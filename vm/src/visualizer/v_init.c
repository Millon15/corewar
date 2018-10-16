/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 18:14:56 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/16 17:31:50 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		put_colors(t_vm *v)
{
	int				i;
	t_colors		*from;
	t_colors		*to;
	t_car			*car;

	i = -1;
	while (++i < MEM_SIZE)
	{
		N->clr[i].main = N->pcolors[MAX_PLAYERS];
		N->clr[i].bold = 0;
		N->clr[i].undrln = 0;
	}
	i = -1;
	car = get_last_car(v);
	while (++i < v->player_amount && car)
	{
		from = N->clr + (car->pc - v->arena);
		to = from + P(i).prog_size;
		from->main = N->ccolors[i];
		while (++from < to)
			from->main = N->pcolors[i];
		car = car->prev;
	}
}

static inline void		init_colors(t_vm *v)
{
	int				i;
	int				j;
	int				l;
	const short		color_pairs[COLOR_AMOUNT * 2] = {
		COLOR_GREEN, COLOR_BLACK,
		COLOR_BLUE, COLOR_BLACK,
		COLOR_YELLOW, COLOR_BLACK,
		COLOR_CYAN, COLOR_BLACK,
		COLOR_DARK, COLOR_BLACK
	};

	i = -1;
	l = 0;
	j = COLOR_DELTA;
	while (++i < COLOR_AMOUNT)
	{
		N->scolors[i] = STAT + i;
		init_pair(N->scolors[i], color_pairs[l], color_pairs[l]);
		N->ccolors[i] = j + COLOR_DELTA;
		init_pair(N->ccolors[i], color_pairs[l + 1], color_pairs[l]);
		N->pcolors[i] = j++;
		init_pair(N->pcolors[i], color_pairs[l], color_pairs[l + 1]);
		l += 2;
	}
}

static inline void		put_border(WINDOW *win)
{
	wattron(win, COLOR_PAIR(BORDER));
	wborder(win, BORDC, BORDC, BORDC, BORDC,
	BORDC, BORDC, BORDC, BORDC);
	wattroff(win, COLOR_PAIR(BORDER));
}

static inline void		init_visualizer(t_vm *v)
{
	N = (t_curses *)ft_memalloc(sizeof(t_curses));
	ft_bzero(&N->w, sizeof(t_widgets));
	initscr();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(false);
	cbreak();
	noecho();
	use_default_colors();
	start_color();
	init_color(COLOR_DARK, 355, 355, 355);
	init_color(COLOR_ORANGE, 755, 500, 0);
	init_pair(BORDER, COLOR_ORANGE, COLOR_ORANGE);
	init_pair(MAIN, COLOR_WHITE, COLOR_BLACK);
	init_pair(INFO, COLOR_WHITE, COLOR_BLACK);
	init_pair(STAT, COLOR_WHITE, COLOR_BLACK);
	init_colors(v);
	put_colors(v);
	(M.is_music) ? play_music(v, MSTART) : false;
}

void					init_windows(t_vm *v)
{
	init_visualizer(v);
	N->mainw = newwin(COMMON_HEIGHT, MW_WIDTH, 0, 0);
	put_border(N->mainw);
	N->infow = newwin(COMMON_HEIGHT, IW_WIDTH, 0, MW_WIDTH - 1);
	wattron(N->infow, COLOR_PAIR(INFO) | A_BOLD);
	put_border(N->infow);
	N->statw = newwin(STAT_HEIGHT, SW_WIDTH, COMMON_HEIGHT - 1, 0);
	wattron(N->statw, COLOR_PAIR(STAT) | A_BOLD);
	put_border(N->statw);
	N->t = clock();
	N->is_run = false;
	N->cycpersec = START_CYCLES_PER_SEC;
	N->is_run = true;
	N->cycpersec = SQMAX_VAL;
	(A.vis_start_value) ? set_start_vis_cycle(v) : false;
	refresh();
	(I.cycle_to_die > 0 && v->head) ? print_one_cycle(v, false) : false;
}
