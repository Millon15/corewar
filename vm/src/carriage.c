/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 17:34:06 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/17 17:14:01 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static const t_op	g_func_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, &live},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, &ld},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, &st},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, &add},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, &sub},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, &and},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, &or},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, &xor},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, &zjmp},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, &ldi},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, &sti},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, &op_fork},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, &lld},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, &lldi},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, &lfork},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, &aff},
	{0, 0, {0}, 0, 0, 0, 0, 0, NULL}
};

static bool			pass_arg_if_invalid(t_car *self, const t_op *cur
	, t_vm *v, int n)
{
	int	i;
	int	padding;
	int	num;

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

static int			vnp_args(t_car *self, const t_op *cur, t_vm *v)
{
	int						padding;
	int						i;
	int						pc_padding;
	bool					inv_arg_fl;

	i = -1;
	pc_padding = 0;
	inv_arg_fl = false;
	while (++i < cur->nb_arg)
	{
		if (!(self->args[i] == cur->args[i] - (self->args[i] ^ cur->args[i]))
		&& (pass_arg_if_invalid(self, cur, v, 0)))
			return (-1);
		if (self->args[i] == T_DIR)
			padding = (cur->label) ? 2 : 4;
		else if (self->args[i] == T_IND)
			padding = 2;
		else if (self->args[i] == T_REG)
			padding = 1;
		else if (pass_arg_if_invalid(self, cur, v, 0))
			return (-1);
		self->arg_val[i] = get_raw_num(v->arena
		+ (PC_IND + self->pc_padding + pc_padding) % MEM_SIZE, padding, v);
		if (self->args[i] == T_REG
		&& (self->arg_val[i] > 16 || self->arg_val[i] < 1))
			inv_arg_fl = true;
		pc_padding += padding;
	}
	self->pc_padding += pc_padding;
	if (inv_arg_fl == true)
		return (-1);
	return (0);
}

static int			vnp_codage(t_car *self, const t_op *cur, t_vm *v)
{
	unsigned char			codage;
	unsigned char			cod[3];
	int						i;

	i = 0;
	ft_bzero((void *)cod, 3);
	codage = (cur->octal) ? (*(v->arena + ((PC_IND + 1) % MEM_SIZE)) >> 2) : 0;
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
		return (-1 * pass_arg_if_invalid(self, cur, v, i));
	return (vnp_args(self, cur, v));
}

static inline void	carriage_refresh(t_car *self)
{
	ft_bzero(&self->args, sizeof(self->args));
	ft_bzero(&self->arg_val, sizeof(self->arg_val));
	self->cur_operation = -1;
	self->cycles_to_wait = -1;
}

void				perform_next_comm(t_car *self, t_vm *v)
{
	if ((*self->pc > REG_NUMBER || *self->pc == 0)
	&& (self->cycles_to_wait < 0))
	{
		move_pc(self, v, 1, false);
		return ;
	}
	while (self->cycles_to_wait < 0 && ++self->cur_operation < REG_NUMBER)
		if (g_func_tab[self->cur_operation].opcode == *self->pc)
			self->cycles_to_wait = g_func_tab[self->cur_operation].cycles;
	if (--self->cycles_to_wait == 0)
	{
		if (vnp_codage(self, &g_func_tab[self->cur_operation], v) < 0)
		{
			move_pc(self, v, self->pc_padding, false);
			self->pc_padding = 0;
			carriage_refresh(self);
			return ;
		}
		g_func_tab[self->cur_operation].f(self, v);
		carriage_refresh(self);
	}
}
