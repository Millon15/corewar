/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_print_stat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 17:22:50 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/02 03:29:55 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		print_stats_directly(t_vm *v, int i, int row
	, double all_pl_lives)
{
	int					min;
	int					coef;
	static const int	clean_delim = SW_WIDTH;
	const double		var =

	(all_pl_lives == 0) ? 0.01 : (double)P(i).total_lives / all_pl_lives;
	min = STAT_LENGTH;
	while (++min < clean_delim)
		wprintw(N->statw, " ");
	min = STAT_LENGTH;
	coef = var * (clean_delim - STAT_LENGTH - 1) + min - 1;
	wattron(N->statw, COLOR_PAIR(N->scolors[i]));
	(P(i).total_lives > 0) ? mvwprintw(N->statw, row, min, " ") : false;
	while (++min < coef)
		wprintw(N->statw, " ");
	wattroff(N->statw, COLOR_PAIR(N->scolors[i]));
}

inline void				print_stats(t_vm *v)
{
	static const int	name_len = SW_WIDTH / 8;
	int					row;
	int					i;
	double				all_pl_lives;

	i = -1;
	all_pl_lives = 0;
	while (++i < v->player_amount)
		all_pl_lives += P(i).total_lives;
	i = -1;
	row = START_ROW_STAT - 1;
	while (++i < v->player_amount)
	{
		mvwprintw(N->statw, ++row, 4, "Player -%d ", i + 1);
		wattron(N->statw, COLOR_PAIR(N->pcolors[i]));
		wprintw(N->statw, "\"%*.*s\"", name_len, name_len, P(i).prog_name);
		wattroff(N->statw, COLOR_PAIR(N->pcolors[i]));
		wprintw(N->statw, " : %6d : ", P(i).total_lives);
		print_stats_directly(v, i, row, all_pl_lives);
	}
	wrefresh(N->statw);
}
