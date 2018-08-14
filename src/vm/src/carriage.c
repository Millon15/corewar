/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 17:34:06 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/14 19:55:55 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

/*
** void		print_the_bit(unsigned char num)
** {
** 	unsigned char		tmp = 0;
** 	int					bit;
**
** 	for(bit = 0; bit < (sizeof(unsigned char) * 8); bit++)
** 	{
** 		tmp <<= 1;
** 		tmp |= num & 0x01;
** 		num >>= 1;
** 	}
** 	for(bit = 0; bit < (sizeof(unsigned char) * 8); bit++)
** 	{
** 		ft_printf("%i ", tmp & 0x01);
** 		tmp >>= 1;
** 	}
** 	ft_putchar('\n');
** }
*/

static int		vnp_args(t_car *self, const t_op *cur)
{
	int						padding;
	int						i;

	i = -1;
	self->pc += 2 * sizeof(t_arg_type);
	while (++i < cur->nb_arg)
	{
		if (!(self->args[i] == cur->args[i] - (self->args[i] ^ cur->args[i])))
			return (-1);
		if (self->args[i] == T_DIR)
			padding = (cur->label) ? 2 : 4;
		else if (self->args[i] == T_IND)
			padding = 2;
		else if (self->args[i] == T_REG)
			padding = 1;
		else
			return (-1);
		self->arg_val[i] = get_raw_num(self->pc, padding);
		self->pc += padding * sizeof(t_arg_type);
	}
	return (0);
}

static int		vnp_codage(t_car *self, const t_op *cur)
{
	unsigned char			codage;
	unsigned char			cod[3];
	int						i;

	i = 0;
	codage = (cur->octal) ? (*(self->pc + 1) >> 2) : 0;
	while (codage <<= 2)
		cod[i++] = codage >> 6;
	i = 0;
	while (i < 3 && cod[i])
	{
		if ((cod[i] & REG_CODE) == REG_CODE)
			self->args[i] = T_REG;
		else if ((cod[i] & DIR_CODE) == DIR_CODE)
			self->args[i] = T_DIR;
		else if ((cod[i] & IND_CODE) == IND_CODE)
			self->args[i] = T_IND;
		else
			return (-1);
		i++;
	}
	if (i != cur->nb_arg)
		return (-1);
	return (vnp_args(self, cur));
}

void			perform_next_comm(t_car *self, t_vm *v)
{
	while (self->cycles_to_wait < 0 && ++self->cur_op_t < REG_NUMBER)
		if (g_func_tab[self->cur_op_t].opcode == *self->pc)
			self->cycles_to_wait = g_func_tab[self->cur_op_t].cycles;
	if (self->cycles_to_wait-- == 0)
	{
		if (vnp_codage(self, &g_func_tab[self->cur_op_t]) < 0)
			return ;
		g_func_tab[self->cur_op_t].f(self, v);
		self->cur_op_t = -1;
	}
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

void			init_car(unsigned char *where, int whom, t_vm *v)
{
	const t_car		*prev = (v->head == NULL) ? NULL : get_last_car(v);
	t_car			**tmp;

	tmp = (v->head == NULL) ? &v->head : &((get_last_car(v))->next);
	(*tmp) = malloc(sizeof(t_car));
	(*tmp)->perform_next_comm = &perform_next_comm;
	(*tmp)->prev = (t_car*)prev;
	(*tmp)->whom = whom;
	(*tmp)->cycles_to_wait = -1;
	(*tmp)->cur_op_t = -1;
	(*tmp)->pc = where;
	(*tmp)->carry = true;
	(*tmp)->next = NULL;
	v->cursors++;
}
