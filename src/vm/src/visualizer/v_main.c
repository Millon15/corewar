/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:56:16 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/20 09:13:05 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static bool				quicker_slower(t_curses *e, t_vm *v)
{
	if (e->c == RUN_QUICKER)
		e->cycles_in_second =
		((e->cycles_in_second + SQBIG_VAL) < SQMAX_VAL) ?
		(e->cycles_in_second + SQBIG_VAL) : SQMAX_VAL;
	else if (e->c == RUN_SLOWER)
		e->cycles_in_second = (e->cycles_in_second > SQBIG_VAL) ?
		(e->cycles_in_second - SQBIG_VAL) : 1;
	else if (e->c == RUN_QUICKER2)
		e->cycles_in_second =
		((e->cycles_in_second + SQSMALL_VAL) < SQMAX_VAL) ?
		(e->cycles_in_second + SQSMALL_VAL) : SQMAX_VAL;
	else if (e->c == RUN_SLOWER2)
		e->cycles_in_second = (e->cycles_in_second > SQSMALL_VAL) ?
		(e->cycles_in_second - SQSMALL_VAL) : 1;
	else
		return (false);
	return (true);
}

void					visualize_the_game(t_vm *v)
{
	t_curses			e;

	fd = open("ggg", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_dprintf(fd, "AAA\n");
	init_windows(&e, v);
	ft_dprintf(fd, "AAA\n");
	while ((e.c = getch()) != EXIT_KEY)
	{
		if (e.c == RUN)
		{
			e.is_run = !e.is_run;
			print_info(&e, v, false);
		}
		else if (e.c == PASS_OVER)
			print_one_cycle(&e, v, true);
		if (e.is_run && clock() >= (e.t + CLOCKS_PER_SEC / e.cycles_in_second))
		{
			print_one_cycle(&e, v, true);
			e.t = clock();
		}
		else if (quicker_slower(&e, v))
			print_info(&e, v, false);
	}
	ft_dprintf(fd, "AAA\n");
	deinit_windows(&e, v);
	ft_dprintf(fd, "AAA\n");
}
