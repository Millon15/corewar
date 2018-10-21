/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infargsop.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 07:05:28 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/21 09:49:18 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFARGSOP_H
# define INFARGSOP_H

/*
** Info structure
*/

# define I				v->info
# define PC_IND			(self->pc - v->arena)

struct					s_info
{
	unsigned int		cursors;
	unsigned int		cur_cycle;
	int					cycle_to_delta;
	int					cycle_to_die;
	int					winner;
};

/*
** Structure of passed args
*/

# define A				v->args
# define IS_VERB(x)		(!A.is_ncurses && (A.verbose_value & (x)))

struct					s_args
{
	unsigned int		is_ncurses : 1;
	unsigned int		is_nostat : 1;
	unsigned int		is_dump : 1;
	unsigned int		is_stealth : 1;
	unsigned int		vis_start_value;
	unsigned int		dump_value;
	unsigned int		verbose_value;
};

/*
** Operations structure
*/

# define PUMPKIN		(res << (8 * i)) >> (8 * (size - 1))
# define SPACE_TO_END	(MEM_SIZE - PC_IND)
# define SHORT_RANGE	(USHRT_MAX + 1)
# define FPOS			16962
# define TNTZEROS		2900
# define FPOS1			21530

struct					s_operations
{
	char				*name;
	unsigned char		nb_arg;
	unsigned char		args[3];
	unsigned char		opcode;
	unsigned int		cycles;
	char				*description;
	bool				octal;
	bool				label;
	void				(*f)(t_car *car, t_vm *v);
};

void					add(t_car *self, t_vm *v);
void					aff(t_car *self, t_vm *v);
void					and(t_car *self, t_vm *v);
void					ld(t_car *self, t_vm *v);
void					ldi(t_car *self, t_vm *v);
void					lfork(t_car *self, t_vm *v);
void					live(t_car *self, t_vm *v);
void					lld(t_car *self, t_vm *v);
void					lldi(t_car *self, t_vm *v);
void					op_fork(t_car *self, t_vm *v);
void					or(t_car *self, t_vm *v);
void					st(t_car *self, t_vm *v);
long					assign_arg(long arg);
int						set_val_neg(t_car *self, t_vm *v, long arg_sum);
int						set_val(t_car *self, t_vm *v, long arg_sum);
void					sti(t_car *self, t_vm *v);
void					sub(t_car *self, t_vm *v);
void					xor(t_car *self, t_vm *v);
void					zjmp(t_car *self, t_vm *v);

#endif
