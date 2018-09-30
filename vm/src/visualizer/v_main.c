/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 21:53:27 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/30 13:44:31 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

inline void				put_car_color_to_arena(t_vm *v)
{
	t_car	*self;

	self = v->head;
	while (self)
	{
		N->clr[PC_IND].main +=
		(N->clr[PC_IND].main < N->ccolors[0]) ? COLOR_DELTA : 0;
		self = self->next;
	}
}

inline void				set_start_vis_cycle(t_vm *v)
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

static bool				quicker_slower(t_vm *v)
{
	if (N->c == RUN_QUICKER)
		N->cycpersec += SQBIG_VAL;
	else if (N->c == RUN_SLOWER)
		N->cycpersec -= SQBIG_VAL;
	else if (N->c == RUN_QUICKER2)
		N->cycpersec += SQSMALL_VAL;
	else if (N->c == RUN_SLOWER2)
		N->cycpersec -= SQSMALL_VAL;
	else
		return (false);
	if (N->cycpersec <= 1)
		N->cycpersec = 1;
	else if (N->cycpersec > SQMAX_VAL)
		N->cycpersec = SQMAX_VAL;
	return (true);
}

#define CLOCK_FORMULA	(N->t + CLOCKS_PER_SEC / N->cycpersec)

void					visualize_the_game(t_vm *v)
{
	init_windows(v);
	while ((N->c = getch()) != EXIT_KEY && v->head)
	{
		if (N->c == RUN)
		{
			N->is_run = !N->is_run;
			print_info(v, false);
		}
		else if (N->c == PASS_OVER)
			print_one_cycle(v, true);
		else if (N->is_run && clock() >= CLOCK_FORMULA)
		{
			N->t = clock();
			print_one_cycle(v, true);
		}
		else if (quicker_slower(v))
			print_info(v, false);
	}
	deinit_windows(v);
}
