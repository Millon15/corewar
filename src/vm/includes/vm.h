/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:57:01 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/14 18:51:54 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <libftprintf.h>
# include <string.h>
# include <op.h>

typedef struct s_args			t_args;
typedef struct s_player			t_player;
typedef struct s_corewar		t_vm;
typedef struct s_function		t_op;
typedef struct s_carriage		t_car;

/*
** Structure of passed args
*/

struct				s_args
{
	unsigned int	is_binary : 1;
	unsigned int	is_ncurses : 1;
	unsigned int	is_stealth : 1;
	unsigned int	is_dump : 1;
	unsigned int	dump_value;

};

/*
** Structure of the single player
*/

struct				s_player
{
	int				fd;
	bool			is_alive;
	char			*filename;
	unsigned int	magic;
	unsigned int	prog_size;
	char			prog_name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	char			source_code[MEM_SIZE];

};

/*
** Functions structure
*/

struct				s_function
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

/*
** Carriage structure
*/

struct				s_carriage
{
	int				whom;
	unsigned int	reg[REG_NUMBER];
	unsigned char	*pc;
	unsigned int	args[3];
	unsigned int	arg_val[3];
	bool			carry;
	int				cycles_to_wait;
	int				cur_op_t;
	void			(*perform_next_comm)(t_car *self, t_vm *v);

	t_car			*prev;
	t_car			*next;
};

/*
** Main corewar structure
*/

struct				s_corewar
{
	int				player_amount;
	t_player		player[MAX_PLAYERS];
	t_args			args;

	unsigned char	arena[MEM_SIZE];
	t_car			*head;

	unsigned int	cursors;
	// unsigned int	cycle;
	// unsigned int	tot_cycle;
	// unsigned int	cycles_to_die;
	// unsigned int	lives;
	// unsigned int	check;
	// unsigned int	bonus;
	// unsigned int	winner;
	// unsigned int	last_alive;

};

/*
** Functions that represents parts of the program
*/

void				fill_players(t_vm *v);
void				fill_arena(t_vm *v);
void				print_arena_to_stdout(t_vm *v);
void				open_files(int ac, char **av, t_vm *v, int i);
void				check_and_obtain_args(int ac, char **av, t_vm *v);

/*
** Carriage related functions
*/

t_car				*get_last_car(t_vm *v);
void				init_car(unsigned char *where, int whom, t_vm *v);

/*
** Operations functions
*/

void				add(t_car *self, t_vm *v);
void				aff(t_car *self, t_vm *v);
void				and(t_car *self, t_vm *v);
void				ld(t_car *self, t_vm *v);
void				ldi(t_car *self, t_vm *v);
void				lfork(t_car *self, t_vm *v);
void				live(t_car *self, t_vm *v);
void				lld(t_car *self, t_vm *v);
void				lldi(t_car *self, t_vm *v);
void				op_fork(t_car *self, t_vm *v);
void				or(t_car *self, t_vm *v);
void				st(t_car *self, t_vm *v);
void				sti(t_car *self, t_vm *v);
void				sub(t_car *self, t_vm *v);
void				xor(t_car *self, t_vm *v);
void				zjmp(t_car *self, t_vm *v);

/*
** Utils
*/

int					meta_reader(const int fd, void *read_in, const int nbytes);
void				meta_printer(const void *to_print, const int nbytes);
unsigned int		read_raw_num(const int fd, const int chars_to_read);
unsigned int		get_raw_num(const unsigned char *ar_ptr,
	const int bytes_to_read);

/*
** Put Error functions
*/

bool				put_usage(const int errnum);
bool				put_error(const int errnum, const char *errstr,
	const int i1, const int i2);

/*
** do al stuf; if you nkow da wae!
*/

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
