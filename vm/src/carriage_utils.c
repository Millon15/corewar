/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 21:59:05 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/07 14:51:00 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void			delete_this_car(t_car **car, t_vm *v)
{
	t_car				*next;

	if (A.is_ncurses)
		N->clr[(*car)->pc - v->arena].main -=
		N->clr[(*car)->pc - v->arena].main >= N->ccolors[0] ? COLOR_DELTA : 0;
	next = (*car)->next;
	if ((*car)->next != NULL)
		(*car)->next->prev = (*car)->prev;
	if ((*car)->prev != NULL)
		(*car)->prev->next = (*car)->next;
	else if ((*car) == v->head)
		v->head = next;
	v->info.cursors--;
	free(*car);
	*car = next;
}

t_car			*get_last_car(t_vm *v)
{
	t_car		*tmp;

	if (v->head == NULL)
		return (NULL);
	tmp = v->head;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void			copy_car(t_car *self, t_vm *v, int arena_pos)
{
	t_car			*new;
	int				i;
	unsigned char	*pc;

	pc = v->arena + (arena_pos);
	init_car(pc, self->name, v);
	new = v->head;
	new->carry = self->carry;
	new->live_cycle = self->live_cycle;
	i = -1;
	while (++i < REG_NUMBER + 1)
		new->reg[i] = self->reg[i];
}

void			init_car(unsigned char *where, int name, t_vm *v)
{
	const t_car		*next = v->head;
	t_car			**tmp;
	static int		id = 0;

	tmp = (v->head == NULL) ? &v->head : &(v->head->prev);
	(*tmp) = ft_memalloc(sizeof(t_car));
	(*tmp)->carry = false;
	(*tmp)->cycles_to_wait = -1;
	(*tmp)->cur_operation = -1;
	(*tmp)->nb_lives = 0;
	(*tmp)->pc_padding = 0;
	(*tmp)->pc = where;
	(*tmp)->live_cycle = I.cur_cycle;
	(*tmp)->id = ++id;
	(*tmp)->pc_ind = where - v->arena;
	ft_bzero(&(*tmp)->args, sizeof((*tmp)->args));
	ft_bzero(&(*tmp)->arg_val, sizeof((*tmp)->arg_val));
	ft_bzero(&(*tmp)->reg, sizeof((*tmp)->reg));
	(*tmp)->reg[1] = name;
	(*tmp)->name = name;
	(*tmp)->next = (t_car*)next;
	(*tmp)->prev = NULL;
	v->head = *tmp;
	v->info.cursors++;
}
