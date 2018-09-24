/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:45 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/23 19:58:50 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		lldi(t_car *self, t_vm *v)
{
	unsigned char	*pc;
	int				arg_sum;
	unsigned int	u_arg_sum;
	unsigned int	first_arg;
	unsigned int	sec_arg;
	int				fa;
	int				sa;
	bool			fa_uint;
	bool			sa_uint;
	bool			as;

	fa_uint = false;
	sa_uint = false;
	as = false;
	if (self->args[0] == T_IND)
	{
		self->arg_val[0] %= IDX_MOD;
		if (self->arg_val[0] > MEM_SIZE - PC_IND)
			pc = &v->arena[self->arg_val[0] - MEM_SIZE - PC_IND];
		else
			pc = &self->pc[self->arg_val[0]];
		first_arg = get_raw_num(pc, REG_SIZE, v);
	}
	else
		first_arg = (self->args[0] == T_REG) ? self->reg[self->arg_val[0]] : self->arg_val[0];
	if (first_arg >= IDX_MOD)
	{
		if (first_arg == IDX_MOD || first_arg % IDX_MOD == 0)
			fa_uint = true;
		else
		{
			first_arg %= IDX_MOD;
			fa = first_arg - IDX_MOD;
		}
	}
	else
		fa = first_arg;
	sec_arg = (self->args[1] == T_REG) ? self->reg[self->arg_val[1]] : self->arg_val[1];
	if (sec_arg >= IDX_MOD)
	{
		if (sec_arg == IDX_MOD || sec_arg % IDX_MOD == 0)
			sa_uint = true;
		else
		{
			sec_arg %= IDX_MOD;
			sa = sec_arg - IDX_MOD;
		}
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
		arg_sum = fa + sa;						//(fa + sa) % IDX_MOD??
	// arg_sum = fa + sa;
	// arg_sum += PC_IND;
	if (as == false/* && u_arg_sum + PC_IND > MEM_SIZE*/)
	{
		// u_arg_sum %= IDX_MOD;
		u_arg_sum += PC_IND;
	}
	else if (as == true)
	{
		// if (arg_sum + PC_IND > MEM_SIZE)
		// arg_sum %= IDX_MOD;
		arg_sum += PC_IND;
	}
	if ((as == true) && (arg_sum < 0))
		pc = &v->arena[MEM_SIZE - mod(arg_sum) % MEM_SIZE];
	else if ((as == true) && (arg_sum >= 0))
		pc = &v->arena[arg_sum % MEM_SIZE];
	else if (as == false)
		pc = &v->arena[u_arg_sum % MEM_SIZE];
	// if (arg_sum > MEM_SIZE - PC_IND)
	// 	pc = &v->arena[arg_sum - MEM_SIZE - PC_IND];
	// else
	// 	pc = &self->pc[arg_sum];
	self->reg[self->arg_val[2]] = get_raw_num(pc, REG_SIZE, v);
	if (A.verbose_value & 4)
	{
		ft_printf("P %4d | lldi %d %d r%d\n", self->id, fa_uint == true ? first_arg : fa,
		sa_uint == true ? sec_arg : sa, self->arg_val[2]);
		// if (as == false && u_arg_sum > MEM_SIZE)
		// 	u_arg_sum = ((u_arg_sum - PC_IND) % IDX_MOD) + PC_IND;
		ft_printf("%8c -> load from %d + %d = %d (with pc and mod %d)\n", '|',
		fa_uint == true ? first_arg : fa, sa_uint == true ? sec_arg : sa,
		(fa_uint == true ? first_arg : fa) + (sa_uint == true ? sec_arg : sa),
		as == false ? u_arg_sum : arg_sum);
	}
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
	// unsigned char	*pc;
	// unsigned int	arg_sum;

	// if (self->args[0] == T_IND)
	// {
	// 	self->arg_val[0] %= IDX_MOD;
	// 	if (self->arg_val[0] > MEM_SIZE - PC_IND)
	// 		pc = &v->arena[self->arg_val[0] - MEM_SIZE - PC_IND];
	// 	else
	// 		pc = &self->pc[self->arg_val[0]];
	// 	arg_sum = get_raw_num(pc, REG_SIZE, v) + self->arg_val[1];
	// 	arg_sum %= IDX_MOD;
	// }
	// else
	// 	arg_sum = self->arg_val[0] + self->arg_val[1];
	// if (arg_sum > MEM_SIZE - PC_IND)
	// 	pc = &v->arena[arg_sum - MEM_SIZE - PC_IND];
	// else
	// 	pc = &self->pc[arg_sum];
	// self->reg[self->arg_val[2]] = get_raw_num(pc, REG_SIZE, v);
	// self->carry = self->arg_val[2] ? false : true;
	// move_pc(self, v, self->pc_padding, false);
	// self->pc_padding = 0;
}
