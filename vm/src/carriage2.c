/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 19:15:48 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/06 20:10:05 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static bool			pass_arg_if_invalid(t_car *self, const t_op *cur)
{
	int				i;
	int				padding;
	int				num;

	i = -1;
	padding = 0;
	num = cur->nb_arg;
	while (++i < num)
	{
		if (self->args[i] == T_DIR)
			padding = (cur->label) ? 2 : 4;
		else if (self->args[i] == T_IND)
			padding = 2;
		else if (self->args[i] == T_REG)
			padding = 1;
		else
			padding = 0;
		self->pc_padding += padding;
	}
	return (true);
}

static int			help_vnp_args(t_car *self, const t_op *cur, int i)
{
	int				padding;

	padding = -1;
	if (!(self->args[i] == cur->args[i] - (self->args[i] ^ cur->args[i]))
	&& (pass_arg_if_invalid(self, cur)))
		return (-1);
	if (self->args[i] == T_DIR)
		padding = (cur->label) ? 2 : 4;
	else if (self->args[i] == T_IND)
		padding = 2;
	else if (self->args[i] == T_REG)
		padding = 1;
	else if (pass_arg_if_invalid(self, cur))
		return (-1);
	return (padding);
}

static int			vnp_args(t_car *self, const t_op *cur, t_vm *v)
{
	int				padding;
	int				i;
	int				pc_padding;
	bool			inv_arg_fl;

	i = -1;
	pc_padding = 0;
	inv_arg_fl = false;
	while (++i < cur->nb_arg)
	{
		if ((padding = help_vnp_args(self, cur, i)) == -1)
			return (-1);
		self->arg_val[i] = get_raw_num(v->arena
		+ find_addr(PC_IND + self->pc_padding + pc_padding), padding, v);
		if (self->args[i] == T_REG
		&& (self->arg_val[i] > 16 || self->arg_val[i] < 1))
			inv_arg_fl = true;
		pc_padding += padding;
	}
	self->pc_padding += pc_padding;
	return ((inv_arg_fl == true) ? -1 : 0);
}

static int			assign_car_args(t_car *self, const t_op *cur, t_vm *v
	, unsigned char cod[3])
{
	int				i;

	i = -1;
	while (++i < 3)
	{
		if ((cod[i] & IND_CODE) == IND_CODE)
			self->args[i] = T_IND;
		else if ((cod[i] & DIR_CODE) == DIR_CODE)
			self->args[i] = T_DIR;
		else if ((cod[i] & REG_CODE) == REG_CODE)
			self->args[i] = T_REG;
	}
	i = -1;
	while (cod[++i] != 0x0)
		;
	if (i < cur->nb_arg)
		return (-1 * pass_arg_if_invalid(self, cur));
	return (vnp_args(self, cur, v));
}

int					vnp_codage(t_car *self, t_vm *v)
{
	const t_op		*cur = g_func_tab + self->cur_operation;
	unsigned char	codage;
	unsigned char	cod[3];
	int				i;

	i = 0;
	ft_bzero((void *)cod, 3);
	codage = (cur->octal) ? (*(v->arena + find_addr(PC_IND + 1)) >> 2) : 0;
	self->pc_padding = 2;
	if (codage == 0x0 && cur->octal)
		return (-1);
	else if (codage == 0x0)
	{
		i = -1;
		self->pc_padding--;
		while (++i < cur->nb_arg)
			self->args[i] = cur->args[i];
		return (vnp_args(self, cur, v));
	}
	while (codage <<= 2)
		cod[i++] = codage >> 6;
	return (assign_car_args(self, cur, v, cod));
}
