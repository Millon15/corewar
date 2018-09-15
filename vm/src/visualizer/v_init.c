/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 18:14:56 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/15 19:29:42 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static const short		color_pairs[10] =
{
		COLOR_GREEN, COLOR_BLACK,
		COLOR_BLUE, COLOR_BLACK,
		COLOR_RED, COLOR_BLACK,
		COLOR_CYAN, COLOR_BLACK,
		COLOR_DARK, COLOR_BLACK
};

static inline void		set_start_vis_cycle(t_vm *v)
{
	int					i;

	while (I.cycle_to_die > 0 && v->head && A.vis_start_value--)
	{
		pass_one_cycle(v);
		i = -1;
		while (++i < MEM_SIZE)
			(v->e->cbold[i] > 0) ? v->e->cbold[i]-- : false;
	}
}

static inline void		put_colors(t_vm *v)
{
	int				i;
	unsigned char	*from;
	unsigned char	*to;
	t_car			*car;

	ft_memset(v->e->acolor, v->e->pcolors[MAX_PLAYERS],
	sizeof(char) * MEM_SIZE);
	ft_bzero(v->e->cbold, sizeof(char) * MEM_SIZE);
	i = -1;
	// while (++i < MEM_SIZE)
	// {
	// 	v->e->acolor[i] = v->e->pcolors[MAX_PLAYERS];
	// 	v->e->cbold[i] = 0;
	// }
	i = -1;
	car = get_last_car(v);
	while (++i < v->player_amount && car)
	{
		from = v->e->acolor + (car->pc - v->arena);
		to = from + P(i).prog_size;
		*from = v->e->ccolors[i];
		while (++from < to)
			*from = v->e->pcolors[i];
		car = car->prev;
	}
}

static inline void		init_colors(t_vm *v)
{
	int					i;
	int					j;
	int					l;

	i = -1;
	l = 0;
	j = COLOR_DELTA;
	// system("echo HUI BLYAD");
	// system("leaks -q corewar");
	// while (++i < MAX_PLAYERS + 1)
	// {
	// 	v->e->ccolors[i] = 0;
	// 	v->e->pcolors[i] = 0;
	// }
	// i = -1;
	ft_bzero(v->e->ccolors, sizeof(short) * (MAX_PLAYERS + 1));
	ft_bzero(v->e->pcolors, sizeof(short) * (MAX_PLAYERS + 1));
	while (++i < (MAX_PLAYERS + 1))
	{
		v->e->ccolors[i] = j + COLOR_DELTA;
		init_pair(v->e->ccolors[i], color_pairs[l + 1], color_pairs[l]);
		v->e->pcolors[i] = j++;
		init_pair(v->e->pcolors[i], color_pairs[l], color_pairs[l + 1]);
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
	init_pair(BORDER, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(MAIN, COLOR_WHITE, COLOR_BLACK);
	init_pair(INFO, COLOR_WHITE, COLOR_BLACK);
}

void					init_windows(t_vm *v)
{
	v->e = (t_curses *)ft_memalloc(sizeof(t_curses));
	init_visualizer();
	init_colors(v);
	put_colors(v);
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
	// v->e->is_run = true;
	// v->e->cycles_per_second = SQMAX_VAL;
	v->e->is_run = false;
	v->e->cycles_per_second = START_CYCLES_PER_SEC;
	(A.vis_start_value) ? set_start_vis_cycle(v) : false;
	refresh();
	if (I.cycle_to_die > 0 && v->head)
		print_one_cycle(v, false);
}

