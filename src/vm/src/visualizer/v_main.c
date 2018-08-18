/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:56:16 by vbrazas           #+#    #+#             */
<<<<<<< HEAD:src/vm/src/visuzlizer.c
/*   Updated: 2018/08/17 15:43:11 by vbrazas          ###   ########.fr       */
=======
/*   Updated: 2018/08/18 19:23:08 by vbrazas          ###   ########.fr       */
>>>>>>> ncurses onbuild2:src/vm/src/visualizer/v_main.c
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		run_cycle(t_curses *e, t_vm *v)
{
	while (e->is_run)
	{
		if (e->t != (clock() / CLOCKS_PER_SEC / e->cycles_in_second))
		{
			print_one_cycle(e, v);
			e->t = clock() / CLOCKS_PER_SEC;
		}
		e->c = getch();
		if (e->c == RUN)
		{
			e->is_run = false;
			return ;
		}
	}
}

static bool				quicker_slower(t_curses *e, t_vm *v)
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

void					visualize_the_game(t_vm *v)
{
	t_curses			e;

	init_windows(&e, v);
	while (true)
	{
		run_cycle(&e, v);
		e.c = getch();
		if (e.c == RUN)
			e.is_run = true;
		else if (e.c == PASS_OVER)
			print_one_cycle(&e, v);
		else if (quicker_slower(&e, v))
			continue ;
		else if (e.c == EXIT_KEY)
			break ;
	}
}
