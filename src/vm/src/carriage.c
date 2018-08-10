/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 17:34:06 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/07 19:57:49 by vbrazas          ###   ########.fr       */
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

void			init_car(unsigned char *where, int whom, t_vm *v)
{
	const t_car		*prev = (v->head == NULL) ? NULL : get_last_car(v);
	t_car			**tmp;

	tmp = (v->head == NULL) ? &v->head : &((get_last_car(v))->next);
	(*tmp) = malloc(sizeof(t_car));
	init_car_vt(*tmp);
	(*tmp)->prev = (t_car*)prev;
	(*tmp)->whom = whom;
	(*tmp)->pc = where;
	(*tmp)->carry = true;
	(*tmp)->next = NULL;
	v->cursors++;
}
