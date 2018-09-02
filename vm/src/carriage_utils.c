/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 21:59:05 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/31 22:56:20 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

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
	// if (v->args.is_ncurses);
	// 	// self->pc_color = v->player[WHOM(self)]->color;
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
	last->prev_pc = cur_car->prev_pc;
	i = -1;
	while (++i < REG_NUMBER + 1)
		last->reg[i] = cur_car->reg[i];
	// ft_memcpy(&last->reg, &cur_car->reg, sizeof(last->reg));
	last->prev_pc_color = PCOLORS + ((int)cur_car->reg[1] * -1) - 1;
}

void			init_car(unsigned char *where, unsigned int whom, t_vm *v)
{
	const t_car		*prev = (v->head == NULL) ? NULL : get_last_car(v);
	t_car			**tmp;

	tmp = (v->head == NULL) ? &v->head : &((get_last_car(v))->next);
	(*tmp) = malloc(sizeof(t_car));
	(*tmp)->carry = true;
	(*tmp)->cycles_to_wait = -1;
	(*tmp)->cur_operation = -1;
	(*tmp)->nb_lives = 0;
	(*tmp)->pc_padding = 0;
	(*tmp)->pc = where;
	(*tmp)->prev_pc = NULL;
	(*tmp)->prev_pc_color = 0;
	ft_memset(&(*tmp)->args, 0, sizeof((*tmp)->args));
	ft_memset(&(*tmp)->arg_val, 0, sizeof((*tmp)->arg_val));
	ft_memset(&(*tmp)->reg, 0, sizeof((*tmp)->reg));
	(*tmp)->reg[1] = whom;
	(*tmp)->prev = (t_car*)prev;
	(*tmp)->next = NULL;
	v->info.cursors++;
}
