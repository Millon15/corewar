/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_widgets.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 17:41:42 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/16 21:50:17 by vbrazas          ###   ########.fr       */
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
	mvwprintw(v->e->infow, row, 4, "%c", '[');
	if (totliv == 0)
		while (++i < WIDGET_LENGTH)
		{
			wattron(v->e->infow, COLOR_PAIR(COLOR_DARKEST));
			wprintw(v->e->infow, "%c", '-');
			wattroff(v->e->infow, COLOR_PAIR(COLOR_DARKEST));
		}
	else
		while (++i < WIDGET_LENGTH)
		{
			if (pval[j] <= cnt++)
				++j && !(cnt = 0);
			wattron(v->e->infow, COLOR_PAIR(v->e->pcolors[j]));
			wprintw(v->e->infow, "%c", '-');
			wattroff(v->e->infow, COLOR_PAIR(v->e->pcolors[j]));
		}
	wprintw(v->e->infow, "%c", ']');
}

void				print_widgets(t_vm *v, int *row)
{
	int			i;
	int			j;
	static int	period = CYCLE_TO_DIE;

	if (period == I.cycle_to_die + CYCLE_DELTA)
	{
		v->e->w.totliv_in_lp = v->e->w.totliv_in_cp;
		ft_memmove(v->e->w.last_pval, v->e->w.pval, 4 * sizeof(int));
		period = I.cycle_to_die;
	}
	v->e->w.totliv_in_cp = 0;
	i = -1;
	while (++i < v->player_amount)
		v->e->w.totliv_in_cp += P(i).lives_in_cp;
	i = -1;
	while (++i < v->player_amount)
		v->e->w.pval[i] = calc_value(P(i).lives_in_cp, v->e->w.totliv_in_cp);
	mvwprintw(v->e->infow, (*row += 2), 4,
	"Live breakdown for current period :");
	print_widget(v, (*row += 1), v->e->w.pval, v->e->w.totliv_in_cp);
	mvwprintw(v->e->infow, (*row += 2), 4, "Live breakdown for last period :");
	print_widget(v, (*row += 1), v->e->w.last_pval, v->e->w.totliv_in_lp);
}
