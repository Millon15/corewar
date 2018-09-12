/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_deinit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 02:41:52 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/12 03:39:32 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		print_winner(t_vm *v)
{
	const char	press[] = "Press any key to finish";
	const char	the_winner[] = "The winner is : ";

	get_winner(v);
	mvwprintw(v->e->infow, COMMON_HEIGHT - 6, ALIGN_CENTER(START_IW_WIDTH,
	ft_strlen(press) + ft_strlen(P(I.winner).prog_name)), "%s", the_winner);
	wattroff(v->e->infow, COLOR_PAIR(INFO) | A_BOLD);
	wattron(v->e->infow, COLOR_PAIR(v->e->pcolors[I.winner]) | A_BOLD);
	wprintw(v->e->infow, "%s", P(I.winner).prog_name);
	wattroff(v->e->infow, COLOR_PAIR(v->e->pcolors[I.winner]) | A_BOLD);
	mvwprintw(v->e->infow, COMMON_HEIGHT - 8,
	ALIGN_CENTER(START_IW_WIDTH, ft_strlen(press)), "%s", press);
	wrefresh(v->e->infow);
	v->e->c = -1;
	while (v->e->c == -1)
		v->e->c = getch();
}

void					deinit_windows(t_vm *v)
{
	if (v->e->c != EXIT_KEY)
		print_winner(v);
	else
		wattroff(v->e->infow, COLOR_PAIR(INFO) | A_BOLD);
	delwin(v->e->mainw);
	delwin(v->e->infow);
	endwin();
	free(v->e->acolor);
	system("reset");
	exit(0);
}
