/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_widgets.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 17:41:42 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/30 13:49:02 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline int	calc_value(double lives_in_cp, double totliv_in_cp)
{
	double	val;
	int		res;

	if ((int)totliv_in_cp == 0)
		return (0);
	val = ((lives_in_cp / totliv_in_cp) * WIDGET_LENGTH);
	res = (int)val;
	if ((double)(val - res) >= 0.5)
		res++;
	return (res);
}

static inline void	print_widget(t_vm *v, int row, int *pval, int totliv)
{
	int		i;
	int		j;
	int		cnt;

	j = 0;
	i = -1;
	cnt = 0;
	mvwprintw(N->infow, row, 4, "%c", '[');
	if (totliv == 0)
	{
		wattron(N->infow, COLOR_PAIR(COLOR_DARK));
		while (++i < WIDGET_LENGTH)
			wprintw(N->infow, "%c", '-');
		wattroff(N->infow, COLOR_PAIR(COLOR_DARK));
	}
	else
		while (++i < WIDGET_LENGTH)
		{
			if (pval[j] <= cnt++)
				++j && !(cnt = 0);
			wattron(N->infow, COLOR_PAIR(N->pcolors[j]));
			wprintw(N->infow, "%c", '-');
			wattroff(N->infow, COLOR_PAIR(N->pcolors[j]));
		}
	wprintw(N->infow, "%c", ']');
}

void				print_widgets(t_vm *v, int *row)
{
	int			i;
	int			j;
	static int	period = CYCLE_TO_DIE;

	if (period != I.cycle_to_die)
	{
		N->w.totliv_in_lp = N->w.totliv_in_cp;
		ft_memmove(N->w.last_pval, N->w.pval, 4 * sizeof(int));
		period = I.cycle_to_die;
	}
	N->w.totliv_in_cp = 0;
	i = -1;
	while (++i < v->player_amount)
		N->w.totliv_in_cp += P(i).lives_in_cp;
	i = -1;
	while (++i < v->player_amount)
		N->w.pval[i] = calc_value(P(i).lives_in_cp, N->w.totliv_in_cp);
	mvwprintw(N->infow, (*row += 2), 4,
	"Live breakdown for current period :");
	print_widget(v, (*row += 1), N->w.pval, N->w.totliv_in_cp);
	mvwprintw(N->infow, (*row += 2), 4, "Live breakdown for last period :");
	print_widget(v, (*row += 1), N->w.last_pval, N->w.totliv_in_lp);
}
