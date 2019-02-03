/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:57:01 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/03 22:36:48 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <curses.h>
# include <time.h>
# include <libftprintf.h>

# include "op.h"
# include "typedefs.h"
# include "infargsop.h"
# include "ncurses.h"
# include "music.h"

/*
** Structure of the single player
*/

# define P(x)		v->player[x]

struct				s_player
{
	bool			is_alive;
	int				fd;

	int				name;
	unsigned int	lives_in_cp;
	unsigned int	magic;
	unsigned int	points;
	unsigned int	prog_size;
	unsigned int	total_lives;

	char			*filename;
	char			prog_name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	char			source_code[MEM_SIZE];
};

/*
** Carriage structure
*/

# define PL_IND(t_car)	(((int)(t_car)->name * -1) - 1)

struct				s_carriage
{
	bool			carry;
	int				name;
	int				cycles_to_wait;
	int				cur_operation;
	int				nb_lives;
	int				pc_padding;
	int				id;
	int				live_cycle;

	unsigned char	*pc;
	int				reg[REG_NUMBER + 1];
	unsigned int	args[3];
	int				arg_val[3];

	t_car			*prev;
	t_car			*next;
};

t_car				*get_last_car(t_vm *v);
void				copy_car(t_car *cc, t_vm *v, unsigned char *pc);
void				delete_this_car(t_car **cur_car, t_vm *v);
void				init_car(unsigned char *where, unsigned int whom, t_vm *v);
void				print_arena(unsigned char *arena, unsigned char to_equate
	, t_car *self, t_vm *v);
void				move_pc(t_car *self, t_vm *v, unsigned int padding
	, bool is_jump_car);

/*
** Main corewar structure
*/

struct				s_corewar
{
	int				player_amount;
	t_player		player[MAX_PLAYERS];

	unsigned char	arena[MEM_SIZE];

	t_car			*head;
	t_curses		*ncurses;

	t_args			args;
	t_info			info;
	t_music			music;
};

void				check_and_obtain_args(int ac, char **av, t_vm *v);
void				fill_players(t_vm *v);
void				fill_arena(t_vm *v);

void				pass_one_cycle(t_vm *v);
void				perform_next_comm(t_car *self, t_vm *v);
int					vnp_codage(t_car *self, const t_op *cur, t_vm *v);
void				get_winner(t_vm *v);

void				kill_process(int *last_check, t_vm *v);
bool				nbr_live_exec(t_car *car);
void				make_live_nil(t_vm *v);
int					ft_abs(int x);

/*
** Utils
*/

int					meta_reader(const int fd, void *read_in, const int nbytes);
void				dump_printer(const void *to_print, const int nbytes);
unsigned int		read_raw_num(const int fd, const int chars_to_read);
int					get_raw_num(const unsigned char *arena,
	const int bytes_to_read, const t_vm *v);

/*
** Put Error functions
*/

bool				put_usage(const int errnum);
bool				put_error(const int errnum, const char *errstr,
	const int i1, const int i2);

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

#endif
