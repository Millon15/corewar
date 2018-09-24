/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_deinit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 02:41:52 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/19 23:37:55 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		print_winner(t_vm *v)
{
	const char	press[] = "Press any key to finish";
	const char	the_winner[] = "The winner is Player No ";

	get_winner(v);
	mvwprintw(N->infow, COMMON_HEIGHT - 8, ALIGN_CENTER(START_IW_WIDTH,
	ft_strlen(press) + 1), "%s%d", the_winner, I.winner + 1);
	wattroff(N->infow, COLOR_PAIR(INFO) | A_BOLD);
	wattron(N->infow, COLOR_PAIR(N->pcolors[I.winner]) | A_BOLD);
	mvwprintw(N->infow, COMMON_HEIGHT - 6,
	ALIGN_CENTER(START_IW_WIDTH, ft_strlen(P(I.winner).prog_name)),
	"%.*s", START_IW_WIDTH, P(I.winner).prog_name);
	wattroff(N->infow, COLOR_PAIR(N->pcolors[I.winner]) | A_BOLD);
	mvwprintw(N->infow, COMMON_HEIGHT - 10,
	ALIGN_CENTER(START_IW_WIDTH, ft_strlen(press)), "%s", press);
	wrefresh(N->infow);
	while (getch() == ERR)
		;
}

void					deinit_windows(t_vm *v)
{
	print_one_cycle(v, false);
	if (N->c != EXIT_KEY)
		print_winner(v);
	else
		wattroff(N->infow, COLOR_PAIR(INFO) | A_BOLD);
	delwin(N->mainw);
	delwin(N->infow);
	endwin();
	exit(0);
}
