/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:55 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/20 17:29:39 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline int			set_val_neg(t_car *self, t_vm *v, int arg_sum)
{
	const unsigned int	res = self->reg[self->arg_val[0]];
	const unsigned int	size = sizeof(res);
	const unsigned int	memsz = (mod(arg_sum) > PC_IND) ? MEM_SIZE : 0;
	int					i;
	int					module;

	module = arg_sum + PC_IND;
	i = -1;
	while (++i < size)
		print_arena(v->arena + (memsz + module + i) % MEM_SIZE, PUMPKIN, self, v);
	return (module);
}

static inline int			set_val(t_car *self, t_vm *v, int arg_sum)
{
	const unsigned int	res = self->reg[self->arg_val[0]];
	const unsigned int	size = sizeof(res);
	unsigned char		*arena;
	int					i;
	int					module;

	arena = v->arena;
	// if (arg_sum > MEM_SIZE - PC_IND)
	// 	module = arg_sum - (MEM_SIZE - PC_IND);
	// else
	// 	module = arg_sum + PC_IND;
	module = PC_IND + arg_sum % IDX_MOD;
	i = -1;
	while (++i < size)
		print_arena(arena + (module + i) % MEM_SIZE, PUMPKIN, self, v);
	return (module);
}

static inline unsigned int	set_uns_val(t_car *self, t_vm *v, unsigned int arg_sum)
{
	const unsigned int	res = self->reg[self->arg_val[0]];
	const unsigned int	size = sizeof(res);
	unsigned char		*arena;
	int					i;
	unsigned int		module;

	arena = v->arena;
	// if (arg_sum > MEM_SIZE - PC_IND)
	// 	module = arg_sum - (MEM_SIZE - PC_IND);
	// else
	// 	module = arg_sum + PC_IND;
	module = PC_IND + arg_sum % IDX_MOD;
	i = -1;
	while (++i < size)
		print_arena(arena + (module + i) % MEM_SIZE, PUMPKIN, self, v);
	return (module);
}

bool						is_four_bytes(t_vm *v, unsigned int val)
{
	unsigned int	res;

	res = val >> 6;
	return ((val >> 6) < 255 ? false : true);
}

void					sti(t_car *self, t_vm *v)
{
	unsigned char		*pc;
	int					arg_sum;
	unsigned int		u_arg_sum;
	unsigned int		first_arg;
	int					fa;
	int					module;
	unsigned int		sec_arg;
	int					sa;
	bool				fa_uint;
	bool				sa_uint;
	bool				as;
	const unsigned int	space_to_end = MEM_SIZE - PC_IND;

	if (self->id == 19 && I.cur_cycle > 2500)
		ft_printf("");
	fa_uint = false;
	sa_uint = false;
	as = false;
	if (self->args[1] == T_IND)
	{
		self->arg_val[1] %= IDX_MOD;
		if (self->arg_val[1] > space_to_end)
			pc = &v->arena[self->arg_val[1] - space_to_end];
		else
			pc = &self->pc[self->arg_val[1]];
		first_arg = get_raw_num(pc, REG_SIZE, v);
	}
	else
		first_arg = self->args[1] == T_REG ? self->reg[self->arg_val[1]] : self->arg_val[1];
	if (first_arg >= IDX_MOD)
	{
		// if (first_arg % IDX_MOD == 256/* && first_arg % MEM_SIZE > space_to_end*/)
		// 	ft_printf("");
		// // 	fa_uint = true;
		// if (first_arg == IDX_MOD || first_arg % IDX_MOD == 0/* || first_arg % IDX_MOD == 256*/) //if first_arg % MEM_SIZE < MEM_SIZE / 2 => fa_uint = true, else false;
		// 	fa_uint = true;
		if (first_arg == IDX_MOD
		|| first_arg % IDX_MOD == 0
		|| first_arg % MEM_SIZE == 0)
		/*|| first_arg % IDX_MOD == first_arg % MEM_SIZE
		|| ((first_arg % IDX_MOD) % (first_arg % MEM_SIZE)) == 0
		|| ((first_arg % MEM_SIZE) % (first_arg % IDX_MOD)) == 0) && (self->args[1] != T_REG)*/			//dikie kostyli
			fa_uint = true;
		else if (((first_arg >> 24) < 255) && self->args[1] == T_REG)
			fa_uint = true;
		else
			fa = first_arg % IDX_MOD - IDX_MOD;
	}
	else
		fa = first_arg;
	sec_arg = self->args[2] == T_REG ? self->reg[self->arg_val[2]] : self->arg_val[2];
	if (sec_arg >= IDX_MOD)
	{
		// if (sec_arg % IDX_MOD == 256 && sec_arg % MEM_SIZE > space_to_end)
		// 	sa_uint = true;
		if ((sec_arg == IDX_MOD || sec_arg % IDX_MOD == 0 || sec_arg % MEM_SIZE == 0 || sec_arg % IDX_MOD == sec_arg % MEM_SIZE
		|| ((sec_arg % IDX_MOD) % (sec_arg % MEM_SIZE)) == 0 || ((sec_arg % MEM_SIZE) % (sec_arg % IDX_MOD)) == 0)/* && (self->args[2] != T_REG)*/)			//dikie kostyli
			sa_uint = true;
		else if (((sec_arg >> 24) < 255) && self->args[1] == T_REG)
			sa_uint = true;
		else
			sa = sec_arg % IDX_MOD - IDX_MOD;
	}
	else
		sa = sec_arg;
		if (fa_uint == true)
	{
		if (mod(sa) > first_arg && sa < 0)
			as = true;
		// if (first_arg + sa >= 0)
		// 	u_arg_sum = (first_arg + sa) + PC_IND;
		// else
		// 	arg_sum = (first_arg + sa) + PC_IND;
	}
		
	else if (sa_uint == true)
	{
		if (mod(fa) > sec_arg && fa < 0)
			as = true;
	}
	else if (fa_uint == false && sa_uint == false)
		as = true;
	if (fa_uint == true && as == true)
		arg_sum = first_arg + sa;
	else if (fa_uint == true && as == false)
		u_arg_sum = first_arg + sa;
	else if (sa_uint == true && as == true)
		arg_sum = fa + sec_arg;
	else if (sa_uint == true && as == false)
		u_arg_sum = fa + sec_arg;
	else if (fa_uint == false && sa_uint == false)
		arg_sum = fa + sa;
	// arg_sum = fa + sa;
	if ((as == true) && (arg_sum < 0))
		module = set_val_neg(self, v, arg_sum);
	else if ((as == true) && (arg_sum >= 0))
		module = set_val(self, v, arg_sum);
	else if (as == false)
		module = set_uns_val(self, v, u_arg_sum);
	// module = (arg_sum < 0) ? set_val_neg(self, v, arg_sum)
	// : set_val(self, v, arg_sum);
	if (!module && ((as == true && !arg_sum) || (as == false && !u_arg_sum)))
		module = PC_IND;
	if (A.verbose_value & 4)
	{
		ft_printf("P %4d | sti r%d %d %d\n", self->id, self->arg_val[0], fa_uint == true ? first_arg : fa,
		sa_uint == true ? sec_arg : sa);
		if (as == false && module > MEM_SIZE)
			module = ((module - PC_IND) % IDX_MOD) + PC_IND;
		ft_printf("%8c -> store to %d + %d = %d (with pc and mod %d)\n", '|', fa_uint == true ? first_arg : fa,
		sa_uint == true ? sec_arg : sa, as == false ? u_arg_sum : arg_sum, module);
	}
	// int i = arg_sum;
	// ft_printf("STI_pc reg_value is: %0.2x\n", self->reg[self->arg_val[0]]);
	// ft_printf("STI_pc is: ");
	// while (i < arg_sum + 10)
		// ft_printf("%0.2x ", self->pc[i++]);
	// ft_putchar('\n');
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
