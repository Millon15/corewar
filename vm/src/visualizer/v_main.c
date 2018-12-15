/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 21:53:27 by vbrazas           #+#    #+#             */
/*   Updated: 2018/12/15 19:11:21 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#define CLOCK_FORMULA	(N->t + CLOCKS_PER_SEC / N->cycpersec)

void					put_car_color_to_arena(t_vm *v)
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

void					set_start_vis_cycle(t_vm *v)
{
	int				i;

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
	if (!(
		((N->c == RUN_QUICKER) && (N->cycpersec += SQBIG_VAL)) ||
		((N->c == RUN_SLOWER) && (N->cycpersec -= SQBIG_VAL)) ||
		((N->c == RUN_QUICKER2) && (N->cycpersec += SQSMALL_VAL)) ||
		((N->c == RUN_SLOWER2) && (N->cycpersec -= SQSMALL_VAL))
	))
		return (false);
	(N->cycpersec < 1) && (N->cycpersec = 1);
	(N->cycpersec > SQMAX_VAL) && (N->cycpersec = SQMAX_VAL);
	return (true);
}

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
		{
			N->is_run = false;
			print_one_cycle(v, true);
		}
		else if (quicker_slower(v))
			print_info(v, false);
		else if (N->is_run && clock() >= CLOCK_FORMULA)
		{
			N->t = clock();
			print_one_cycle(v, true);
		}
	}
	deinit_windows(v);
}
