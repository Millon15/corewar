/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_print_stat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 17:22:50 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/21 06:21:08 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#define STAT_STR_LENGTH		25
#define OFFSET				55

static void					print_stats_directly(t_vm *v, int i, int row
	, double all_pl_lives)
{
	int						min;
	int						coef;
	static const int		clean_delim = SW_WIDTH - 2;
	const double			var =

	(all_pl_lives == 0) ? 0.0 : (double)P(i).total_lives / all_pl_lives;
	min = OFFSET;
	wmove(N->statw, row, min);
	while (++min <= clean_delim)
		waddch(N->statw, ' ');
	min = OFFSET;
	coef = var * clean_delim + min;
	if (coef > clean_delim)
		coef = clean_delim;
	wattron(N->statw, COLOR_PAIR(N->scolors[i]));
	(P(i).total_lives > 0) ? mvwprintw(N->statw, row, min, " ") : false;
	while (++min < coef)
		waddch(N->statw, ' ');
	wattroff(N->statw, COLOR_PAIR(N->scolors[i]));
}

void						print_stats(t_vm *v)
{
	int						row;
	int						i;
	double					all_pl_lives;

	i = -1;
	all_pl_lives = 0;
	while (++i < v->player_amount)
		all_pl_lives += P(i).total_lives;
	i = -1;
	row = START_ROW - 1;
	while (++i < v->player_amount)
	{
		mvwprintw(N->statw, ++row, 4, "Player -%d ", i + 1);
		wattron(N->statw, COLOR_PAIR(N->pcolors[i]));
		wprintw(N->statw, "\"%*.*s\"", STAT_STR_LENGTH, STAT_STR_LENGTH
		, P(i).prog_name);
		wattroff(N->statw, COLOR_PAIR(N->pcolors[i]));
		wprintw(N->statw, " | %8d : ", P(i).total_lives);
		print_stats_directly(v, i, row, all_pl_lives);
	}
	wrefresh(N->statw);
}
