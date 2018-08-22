/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 21:59:05 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/22 22:47:37 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

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

void			copy_car_to_end(t_car *cur_car, t_vm *v)
{
	t_car		*last;

	last = get_last_car(v);
	last->next = malloc(sizeof(t_car));
	last->next->carry = cur_car->carry;
	last->next->cycles_to_wait = cur_car->cycles_to_wait;
	last->next->cur_operation = cur_car->cur_operation;
	last->next->nb_lives = cur_car->nb_lives;
	last->next->pc_padding = cur_car->pc_padding;
	last->next->pc = cur_car->pc;
	last->next->reg[1] = cur_car->reg[1];
	last->next->prev = last;
	last->next->next = NULL;
	v->info.cursors++;
}

void			delete_this_car(t_car *cur_car, t_vm *v)
{
	if (cur_car->next != NULL)
		cur_car->next->prev = cur_car->prev;
	if (cur_car->prev != NULL)
		cur_car->prev->next = cur_car->next;
	else if (cur_car == v->head)
		v->head = cur_car->next;
	v->info.cursors--;
	free(cur_car);
}

void			move_pc(t_car *self, t_vm *v, unsigned int padding)
{
	self->pc = (v->arena + (self->pc - v->arena + padding) % MEM_SIZE);
	if (v->args.is_ncurses);
		// self->pc_color = v->player[WHOM(self)]->color;
}
