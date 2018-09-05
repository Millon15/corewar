/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 21:59:05 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/05 20:50:15 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void			delete_this_car(t_car **cur_car, t_vm *v)
{
	t_car		*next;

	next = (*cur_car)->next;
	if ((*cur_car)->next != NULL)
		(*cur_car)->next->prev = (*cur_car)->prev;
	if ((*cur_car)->prev != NULL)
		(*cur_car)->prev->next = (*cur_car)->next;
	else if ((*cur_car) == v->head)
		v->head = (*cur_car)->next;
	v->info.cursors--;
	free(*cur_car);
	*cur_car = next;
}

void			move_pc(t_car *self, t_vm *v, unsigned int padding)
{
	self->pc = (v->arena + (self->pc - v->arena + padding) % MEM_SIZE);
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

void			copy_car(t_car *cur_car, t_vm *v, unsigned char *pc)
{
	t_car		*last;
	int			i;

	init_car(pc, cur_car->reg[1], v);
	last = get_last_car(v);
	last->carry = cur_car->carry;
	last->is_fork = true;
	i = -1;
	while (++i < REG_NUMBER + 1)
		last->reg[i] = cur_car->reg[i];
	last->color_pc = cur_car->color_pc;
	last->color = PCOLORS + PL_IND(cur_car);
}

void			init_car(unsigned char *where, unsigned int whom, t_vm *v)
{
	const t_car		*prev = (v->head == NULL) ? NULL : get_last_car(v);
	t_car			**tmp;
	static int		id = 0;

	tmp = (v->head == NULL) ? &v->head : &((get_last_car(v))->next);
	(*tmp) = malloc(sizeof(t_car));
	(*tmp)->carry = true;
	(*tmp)->is_fork = false;
	(*tmp)->cycles_to_wait = -1;
	(*tmp)->cur_operation = -1;
	(*tmp)->nb_lives = 0;
	(*tmp)->pc_padding = 0;
	(*tmp)->pc = where;
	(*tmp)->color_pc = NULL;
	(*tmp)->color = 0;
	(*tmp)->id = ++id;
	(*tmp)->is_alive = true;
	(*tmp)->death_cycle = 0;
	(*tmp)->live_cycle = I.cur_cycle;
	ft_memset(&(*tmp)->args, 0, sizeof((*tmp)->args));
	ft_memset(&(*tmp)->arg_val, 0, sizeof((*tmp)->arg_val));
	ft_memset(&(*tmp)->reg, 0, sizeof((*tmp)->reg));
	(*tmp)->reg[1] = whom;
	(*tmp)->prev = (t_car*)prev;
	(*tmp)->next = NULL;
	v->info.cursors++;
}
