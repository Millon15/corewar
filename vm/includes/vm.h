/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:57:01 by vbrazas           #+#    #+#             */
/*   Updated: 2018/10/21 09:55:05 by vbrazas          ###   ########.fr       */
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

	unsigned int	name;
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
	unsigned int	name;
	int				cycles_to_wait;
	int				cur_operation;
	int				nb_lives;
	int				pc_padding;
	int				id;
	int				live_cycle;

	unsigned char	*pc;
	unsigned int	reg[REG_NUMBER + 1];
	unsigned int	args[3];
	unsigned int	arg_val[3];

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
unsigned int		get_raw_num(const unsigned char *arena,
	const int bytes_to_read, const t_vm *v);

/*
** Put Error functions
*/

bool				put_usage(const int errnum);
bool				put_error(const int errnum, const char *errstr,
	const int i1, const int i2);

#endif
