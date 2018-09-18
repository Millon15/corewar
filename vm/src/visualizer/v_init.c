/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 18:14:56 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/18 15:52:52 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		set_start_vis_cycle(t_vm *v)
{
	int					i;

	while (I.cycle_to_die > 0 && v->head && A.vis_start_value--)
	{
		pass_one_cycle(v);
		i = -1;
		while (++i < MEM_SIZE)
			(N->clr[i].bold > 0) ? N->clr[i].bold-- : false;
	}
}

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
		N->ccolors[i] = j + COLOR_DELTA;
		init_pair(N->ccolors[i], color_pairs[l + 1], color_pairs[l]);
		N->pcolors[i] = j++;
		init_pair(N->pcolors[i], color_pairs[l], color_pairs[l + 1]);
		l += 2;
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
	init_color(COLOR_DARKEST, 0, 0, 0);
	init_pair(BORDER, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(MAIN, COLOR_WHITE, COLOR_BLACK);
	init_pair(INFO, COLOR_WHITE, COLOR_BLACK);
}

void					init_windows(t_vm *v)
{
	N = (t_curses *)ft_memalloc(sizeof(t_curses));
	ft_bzero(&N->w, sizeof(t_widgets));
	init_visualizer();
	init_colors(v);
	put_colors(v);
	N->mainw = newwin(COMMON_HEIGHT, START_MW_WIDTH, 0, 0);
	wattron(N->mainw, COLOR_PAIR(BORDER));
	wborder(N->mainw, BORDC, BORDC, BORDC, BORDC,
	BORDC, BORDC, BORDC, BORDC);
	wattroff(N->mainw, COLOR_PAIR(BORDER));
	N->infow = newwin(COMMON_HEIGHT, START_IW_WIDTH, 0, START_MW_WIDTH - 1);
	wattron(N->infow, COLOR_PAIR(BORDER));
	wborder(N->infow, BORDC, BORDC, BORDC, BORDC,
	BORDC, BORDC, BORDC, BORDC);
	wattroff(N->infow, COLOR_PAIR(BORDER));
	wattron(N->infow, COLOR_PAIR(INFO) | A_BOLD);
	N->t = clock();
	// N->is_run = true;
	// N->cycpersec = SQMAX_VAL;
	N->is_run = false;
	N->cycpersec = START_CYCLES_PER_SEC;
	(A.vis_start_value) ? set_start_vis_cycle(v) : false;
	refresh();
	if (I.cycle_to_die > 0 && v->head)
		print_one_cycle(v, false);
}
