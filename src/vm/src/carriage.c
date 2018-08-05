/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 17:34:06 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/05 20:10:24 by vbrazas          ###   ########.fr       */
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
	t_car		*prev;

	if (v->head == NULL)
	{
		v->head = malloc(sizeof(t_car));
		v->head->prev = NULL;
		v->head->where = where;
		v->head->whom = whom;
		v->head->next = NULL;
	}
	else
	{
		prev = get_last_car(v);
		prev->next = malloc(sizeof(t_car));
		prev->next->prev = prev;
		prev->next->where = where;
		prev->next->whom = whom;
		prev->next->next = NULL;
	}
	v->cursors++;
}
