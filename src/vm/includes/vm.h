/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:57:01 by vbrazas           #+#    #+#             */
/*   Updated: 2018/08/20 08:57:26 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <libftprintf.h>
# include <op.h>

# define MOVE_PC(aptr, pc, how_much)	(aptr + (pc - aptr + how_much) % MEM_SIZE)
# define I								v->info

typedef struct s_args			t_args;
typedef struct s_player			t_player;
typedef struct s_corewar		t_vm;
typedef struct s_function		t_op;
typedef struct s_carriage		t_car;
typedef struct s_info			t_info;
typedef struct s_curses			t_curses;

/*
** ncurses visualizer info
*/

# include <curses.h>
# include <time.h>

# define EXIT_KEY		27
# define RUN			' '
# define PASS_OVER		's'
# define RUN_SLOWER		'q'
# define RUN_QUICKER	'r'
# define RUN_SLOWER2	'w'
# define RUN_QUICKER2	'e'

# define BORDC			'*'
# define SQMAX_VAL		1000
# define SQBIG_VAL		10
# define SQSMALL_VAL	1
# define WHEIGHT		(MEM_SIZE / 64 + 4)
# define MW_WIDTH		(64 * 3 + 7)
# define IW_WIDTH		(MW_WIDTH / 2.5)
# define CL_PADD		20
# define ROW_MAIN		1
# define ROW_INFO		2

# define ALIGN_CENTER(w, l)		((w - l) / 2)

# define BORDER			1
# define MAIN			2
# define INFO			3
# define COLOR_DARK		8
// # define COLOR_SILVER	9
# define P1				10
# define P2				11
# define P3				12
# define P4				13

struct				s_curses
{
	WINDOW			*mainw;
	WINDOW			*infow;
	clock_t			t;
	char			c;
	bool			is_run;
	unsigned int	cycles_in_second;

};

/*
** Info structure
*/

struct				s_info
{
	t_car			*cur_car;
	unsigned int	cursors;
	unsigned int	cur_cycle;
	unsigned int	cycle_to_die;
	// unsigned int	lives;
	// unsigned int	check;
	// unsigned int	bonus;
	// unsigned int	winner;
	// unsigned int	last_alive;

};

/*
** Structure of passed args
*/

struct				s_args
{
	int				is_binary : 1;
	int				is_ncurses : 1;
	int				is_stealth : 1;
	int				is_dump : 1;
	int				dump_value;

};

/*
** Structure of the single player
*/

struct				s_player
{
	int				fd;
	unsigned int	name;
	unsigned int	lives_in_cp;
	bool			is_alive;
	char			*filename;
	unsigned int	magic;
	unsigned int	points;
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
	char			*name;
	unsigned char	nb_arg;
	unsigned char	args[3];
	unsigned char	opcode;
	unsigned int	cycles;
	char			*description;
	bool			octal;
	bool			label;
	void			(*f)(t_car *car, t_vm *v);

};

/*
** Carriage structure
*/

struct				s_carriage
{
	unsigned int	whom;
	unsigned int	reg[REG_NUMBER];
	unsigned char	*pc;
	unsigned int	args[3];
	unsigned int	arg_val[3];
	bool			carry;
	int				cycles_to_wait;
	int				cur_operation;
	int				nb_lives;
	int				pc_padding;

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

	unsigned char	arena[MEM_SIZE];
	t_car			*head;

	t_args			args;
	t_info			info;

};
int fd;
/*
** Functions that represents main parts of the program
*/

void				check_and_obtain_args(int ac, char **av, t_vm *v);
void				fill_players(t_vm *v);
void				fill_arena(t_vm *v);
void				print_arena(t_vm *v);

void				pass_one_cycle(t_vm *v);
void				perform_next_comm(t_car *self, t_vm *v);

/*
** Visualizer functions
*/

void				visualize_the_game(t_vm *v);
void				print_one_cycle(t_curses *e, t_vm *v, bool is_pass_cycle);
void				print_main(t_curses *e, t_vm *v);
void				print_info(t_curses *e, t_vm *v, bool is_print_full_info);
void				init_windows(t_curses *e, t_vm *v);
void				deinit_windows(t_curses *e, t_vm *v);

/*
** Carriage related functions
*/

t_car				*get_last_car(t_vm *v);
void				copy_car_to_end(t_car *cur_car, t_vm *v);
void				delete_this_car(t_car *cur_car, t_vm *v);
void				init_car(unsigned char *where, unsigned int whom, t_vm *v);

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

void				kill_process(t_car *car, t_vm *v);
bool				nbr_live_exec(t_car *car);
void				make_live_nil(t_vm *v);

#endif
