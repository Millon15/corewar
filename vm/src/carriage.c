/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 17:34:06 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/11 07:16:03 by vbrazas          ###   ########.fr       */
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

static bool		pass_arg_if_invalid(t_car *self, const t_op *cur, t_vm *v, int n)
{
	int	i;
	int	padding;
	int	num;

	i = -1;
	padding = 0;
	// num = !n ? cur->nb_arg : n;
	num = cur->nb_arg;
	while (++i < num)
	{
		if (self->args[i] == T_DIR)
			padding = (cur->label) ? 2 : 4;
		else if (self->args[i] == T_IND)
			padding = 2;
		else if (self->args[i] == T_REG)
			padding = 1;
		self->pc_padding += padding;		
	}
	return (true);
}

static int		vnp_args(t_car *self, const t_op *cur, t_vm *v)
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
		if (!(self->args[i] == cur->args[i] - (self->args[i] ^ cur->args[i])) &&
		(pass_arg_if_invalid(self, cur, v, 0)))
			return (-1);
		if (self->args[i] == T_DIR)
			padding = (cur->label) ? 2 : 4;
		else if (self->args[i] == T_IND)
			padding = 2;
		else if (self->args[i] == T_REG)
			padding = 1;
		else if (pass_arg_if_invalid(self, cur, v, 0))
			return (-1);
		self->arg_val[i] = get_raw_num(v->arena + ((self->pc - v->arena) + self->pc_padding + pc_padding) % MEM_SIZE, padding);
		// if (self->args[i] == T_REG && self->arg_val[i] > 16)
		// 	inv_arg_fl = true;
		pc_padding += padding;
	}
	self->pc_padding += pc_padding;
	// if (inv_arg_fl == true)
	// {
	// 	move_pc(self, v, self->pc_padding, false);
	// 	return (-1);
	// }
	// i = -1;
	// while (++i < cur->nb_arg)
	// 	ft_printf("%dL: %0.2x\n", i, self->arg_val[i]);
	// ft_printf("!!!self->arg_val[%d] :%0.2x!!!, self->pc_padding: %d\n", i- 1, self->arg_val[i - 1], self->pc_padding);	
	return (0);
}

int				duplicate_args(const t_op *cur)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (cur->args[i] == (T_DIR | T_IND) ||
		cur->args[i] == (T_REG | T_IND) || cur->args[i] == (T_IND | T_DIR)
		|| cur->args[i] == (T_REG | T_IND | T_DIR))
			return (1);
		i++;
	}
	return (0);
}

static int		vnp_codage(t_car *self, const t_op *cur, t_vm *v)
{
	unsigned char			codage;
	unsigned char			cod[3];
	int						i;

	i = 0;
	if (self->id == 16)
		ft_printf("");
	if (!(MEM_SIZE - (PC_DELTA)))
		codage = (cur->octal) ? (*v->arena >> 2) : 0;
	else
	{
		codage = (cur->octal) ? (*(self->pc + 1) >> 2) : 0;
		// ft_printf("*(self->pc + 1) %0.2x: ", *(self->pc + 1));
	}
	self->pc_padding = 1;
	// ft_printf("codage: %d\n", codage);
	if (codage == 0x0 && duplicate_args(cur))
	{
		self->pc_padding++;
		return (-1);
	}
	else if (codage == 0x0)
	{
		i = -1;
		while (++i < cur->nb_arg)
			self->args[i] = cur->args[i];
		return (vnp_args(self, cur, v));
	}
	else
		self->pc_padding++;
	if (self->id == 16)
		ft_printf("");
	while (codage <<= 2)
		cod[i++] = codage >> 6;

	// i = 0;
	// ft_putstr("-------------------------------------->\nOur pc is: \n");
	// while (i < 10)
	// 	ft_printf("%0.2x ", self->pc[i++]);
	// ft_putchar('\n');
	// ft_putstr("The end of our pc\n-------------------------------------->\n");

	i = -1;
	while (++i < 3 /*&& cod[i] != 0x0*/)
	{
		// ft_printf("cod[%d] : %0.2d\n", i, cod[i]);
		if ((cod[i] & IND_CODE) == IND_CODE)
			self->args[i] = T_IND;
		else if ((cod[i] & DIR_CODE) == DIR_CODE)
			self->args[i] = T_DIR;
		else if ((cod[i] & REG_CODE) == REG_CODE)
			self->args[i] = T_REG;
		// else
		// 	return (-1);
	}
	i = -1;
	while (cod[++i] != 0x0)
		;
	if (i != cur->nb_arg)
		return (-1 * pass_arg_if_invalid(self, cur, v, i));
	return (vnp_args(self, cur, v));
}

void			perform_next_comm(t_car *self, t_vm *v)
{
	if ((*self->pc > REG_NUMBER || *self->pc == 0) && (self->cycles_to_wait < 0))
	{
		move_pc(self, v, 1, false);
		return ;
	}
	while (self->cycles_to_wait < 0 && ++self->cur_operation < REG_NUMBER)
		if (g_func_tab[self->cur_operation].opcode == *self->pc)
		{
			self->cycles_to_wait = g_func_tab[self->cur_operation].cycles;
			if (self->id == 16)
				ft_printf("");
		}
	// if (self->cur_operation >= REG_NUMBER || *self->pc == 0)
	// {
	// 	move_pc(self, v, 1, false);
	// 	self->cur_operation = -1;
	// 	self->cycles_to_wait = -1;
	// 	return ;
	// }
	if (--self->cycles_to_wait == 0)
	{

		// if (I.cur_cycle == 2754)
		// {
		// 	dprintf(fd, "oper name: %s\n", g_func_tab[self->cur_operation].name);
		// 	dprintf(fd, "cycles num: %d\n", g_func_tab[self->cur_operation].cycles);
		// }
		// dprintf(fd, "cur_car: %p | I.cur_cycle: %u\n", self->prev, I.cur_cycle);

		// int i = 0;
		// ft_putstr("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~>\nOur pc is: \n");
		// while (i < 20)
		// 	ft_printf("%0.2x ", self->pc[i++]);
		// ft_putchar('\n');
		// ft_putstr("The end of our pc\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~>\n");
		// ft_printf("oper name: %s\n", g_func_tab[self->cur_operation].name);
		if (vnp_codage(self, &g_func_tab[self->cur_operation], v) < 0)
		{
			move_pc(self, v, self->pc_padding, false);
			self->pc_padding = 0;
			ft_bzero(&self->args, sizeof(self->args));
			ft_bzero(&self->arg_val, sizeof(self->arg_val));
			self->cur_operation = -1;
			self->cycles_to_wait = -1;
			return ;
		}
		if (self->id == 16)
			ft_printf("");
		g_func_tab[self->cur_operation].f(self, v);
		// i = 0;
		// ft_putstr("-------------------------------------->\nOur pc is: \n");
		// while (i < 20)
		// 	ft_printf("%0.2x ", self->pc[i++]);
		// ft_putchar('\n')-;
		// ft_putstr("The end of our pc\n-------------------------------------->\n");
		ft_bzero(&self->args, sizeof(self->args));
		ft_bzero(&self->arg_val, sizeof(self->arg_val));
		self->cur_operation = -1;
		self->cycles_to_wait = -1;
	}
}
